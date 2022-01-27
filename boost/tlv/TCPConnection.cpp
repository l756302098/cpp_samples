/*
 * TCPConnection.h
 *
 *    Created on: Mar 8, 2021
 *            Author: ubuntu
 */

#include "TCPConnection.h"
#include "Thread.h"
#include "Time.h"

// temp

std::string DecIntToHexStr(long long num)
{
    std::string str;
    long long Temp = num / 16;
    int left = num % 16;
    if (Temp > 0)
        str += DecIntToHexStr(Temp);
    if (left < 10)
        str += (left + '0');
    else
        str += ('A' + left - 10);
    return str;
}

std::string DecIntToHexStr(std::uint8_t num)
{
    auto str = DecIntToHexStr((long long )num);
    str = "0x" + str;
    return str;
}

namespace trs
{

TCPConnection::TCPConnection(std::shared_ptr<tcp::socket> sock,
        std::function<void(std::shared_ptr<TCPConnection>)> funcDisconnected,
        std::uint64_t processIntervalUs)
    : funcDisconnected(funcDisconnected), processIntervalUs(processIntervalUs)
{
    this->sock = sock;
    running = true;
}


TCPConnection::~TCPConnection() {}

void TCPConnection::Start()
{
    ReadHeader();

    sendThread = std::thread(
        std::bind(&TCPConnection::Run, this)
    );

    sendThread.detach();
}

void TCPConnection::Stop()
{
    running = false;
    try {
        if (sock->is_open())
        {
            std::cout << "close socket." << std::endl;
            sock->shutdown(tcp::socket::shutdown_both);  
            //sock->close();
        }
    } catch (...) {
        std::cout << "exception in closing socket." << std::endl;
    }

    cvSendQueue.notify_one();


//    if (sendThread.joinable())
//    {
//        sendThread.join();
//    }
}

void TCPConnection::ReadHeader()
{
    // for keep alive
    auto self = shared_from_this();

    auto header = std::make_shared<TLVMessage::Header>();

    boost::asio::async_read(
        *sock, boost::asio::buffer(header->raw(), TLVMessage::SIZE_OF_HEADER),
        std::bind(&TCPConnection::OnHeaderReceived, this, self, header, std::placeholders::_1, std::placeholders::_2));
}


void TCPConnection::ReadBody(std::shared_ptr<TLVMessage::Header> header) {

    std::cout << "ReadBody" << std::endl;
    auto self = shared_from_this();

    auto msg = TLVMessage::Generate(header);

    boost::asio::async_read(
        *sock, boost::asio::buffer(msg->body, msg->header.bodyLength),
        std::bind(&TCPConnection::OnBodyReceived, this, self, msg, std::placeholders::_1, std::placeholders::_2));
}

void TCPConnection::OnHeaderReceived(std::shared_ptr<TCPConnection> self,
        std::shared_ptr<TLVMessage::Header> header,
        boost::system::error_code ec, std::size_t receivedLength)
{
    std::cout << "Read header from remote, size: " << receivedLength << std::endl;
    std::string out = "";
    for (uint i = 0; i < receivedLength; ++i)
    {
        uint8_t* data = header->raw();
        out.append(DecIntToHexStr(data[i])).append(" ");
    }
    std::cout << "data:" << out<< std::endl;

    if (ec != boost::system::errc::success
            || TLVMessage::SIZE_OF_HEADER != receivedLength)
    {
        //Stop();
        std::cout << "an exception occurred after receive message." << std::endl;
        funcDisconnected(shared_from_this());
        return;
    }

    header->decode();

    std::cout << "header.bodyLength, size: " << header->bodyLength << std::endl;
    if (header->bodyLength > 0)
    {
        ReadBody(header);
    }
    else
    {
        funcMessageReceived(TLVMessage::Generate(header));
        ReadHeader();
    }
}

void TCPConnection::OnBodyReceived(std::shared_ptr<TCPConnection> self,
        std::shared_ptr<TLVMessage> msg,
        boost::system::error_code ec, std::size_t receivedLength)
{
    std::cout << "received body length:" << receivedLength << std::endl;
    std::string out = "";
    for (uint i = 0; i < receivedLength; ++i)
    {
        uint8_t* data = msg->GetDataPointerWithOffset();
        out.append(DecIntToHexStr(data[i])).append(" ");
        printf("%02X ",data[i]);
    }
    printf("\n");
    //std::cout << "data:" << out;

    if (ec != boost::system::errc::success
            || msg->header.bodyLength != receivedLength)
    {
        //Stop();
        std::cout << "an exception occurred after receive message." << std::endl;
        funcDisconnected(shared_from_this());
        return;
    }

    funcMessageReceived(msg);
//    std::this_thread::yield();
    if (processIntervalUs != 0)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(processIntervalUs));
    }
    ReadHeader();
}

void TCPConnection::Run()
{
//    sched_param param = {99};
//    pthread_setschedparam(sendThread.native_handle(), SCHED_RR, &param);

    while (running)
    {
        std::unique_lock<std::mutex> lck(mtxSendQueueNoti);
        cvSendQueue.wait_for(lck, std::chrono::milliseconds(100));

        while (!msgQueue.empty())
        {
            auto msg = msgQueue.pop();
            Send(msg);

            if (processIntervalUs != 0)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(processIntervalUs));
            }
        }
    }
}

void TCPConnection::PendMessage(std::shared_ptr<TLVMessage> msg)
{
    msgQueue.push(msg);
    cvSendQueue.notify_one();
}


bool TCPConnection::Send(std::uint8_t* data, size_t size)
{
    boost::system::error_code ec;
    size_t written = 0;
    size_t restSize = size;
    std::uint8_t* cache = data;

    // send message
    do {
        written = sock->write_some(boost::asio::buffer(cache, restSize), ec);
        if (ec)
        {
            break;
        }
        cache += written;
        restSize -= written;
    } while (ec == boost::system::errc::success && running && restSize > 0);

    if (ec != boost::system::errc::success)
    {
        Stop();
        std::cout << "a fatal error occurs while sending data, system exit." << std::endl;
        funcDisconnected(shared_from_this());
        return false;
    }

    return true;
}

void TCPConnection::Send(std::shared_ptr<TLVMessage> msg)
{
    //auto start = swr::util::Now();
    auto header = msg->header;
    auto size = msg->header.bodyLength + TLVMessage::SIZE_OF_HEADER;
    header.encode();

    char* sendBuf = new char[size];
    memcpy(sendBuf, &header, TLVMessage::SIZE_OF_HEADER);
    memcpy(sendBuf + TLVMessage::SIZE_OF_HEADER, msg->body, msg->header.bodyLength);

    try {
        boost::asio::write(*sock, boost::asio::buffer(sendBuf, size));
    } catch (...) {
        Stop();
        std::cout << "a fatal error occurs while sending data, system exit." << std::endl;
        funcDisconnected(shared_from_this());
    }
//    boost::asio::write(*sock, boost::asio::buffer((std::uint8_t*)&header, TLVMessage::SIZE_OF_HEADER));
//    boost::asio::write(*sock, boost::asio::buffer(msg->body, msg->header.bodyLength ));

//    if(Send(header.raw(), TLVMessage::SIZE_OF_HEADER) && msg->header.bodyLength > 0)
//    {
//        Send(msg->body, msg->header.bodyLength);
//    }
//    std::cout << "send cost: " << swr::util::Now() - start;
}

}



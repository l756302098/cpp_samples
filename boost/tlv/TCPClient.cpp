/*
 * tcp_client.cpp
 *
 *  Created on: Mar 9, 2021
 *      Author: ubuntu
 */

#include "TCPClient.h"
#include "Thread.h"

namespace trs
{

TCPClient::TCPClient(
      std::string address,
      int port,
      std::function<void(std::shared_ptr<TCPConnection>)> on_connected,
      std::function<void(std::shared_ptr<TCPConnection>)> on_disconnected,
      std::uint64_t processIntervalUs
      )
{
    ep = tcp::endpoint(boost::asio::ip::address::from_string(address), port);
    sock = std::make_shared<tcp::socket>(ioContext);
    OnConnected = on_connected;
    OnDisconnected = on_disconnected;
    this->processIntervalUs = processIntervalUs;
}

void TCPClient::Run()  {
    boost::system::error_code ec;
    boost::asio::io_service::work work(ioContext);
//    while (1)
//    {
//        ioContext.poll_one(ec);
//        std::this_thread::sleep_for(std::chrono::microseconds(processIntervalUs));
//    }
    ioContext.run(ec);
}

bool TCPClient::Connect()
{
    boost::system::error_code ec;
    sock->connect(ep,ec);
    if(ec)
    {
        return false;
    }
    tcp::no_delay option(true);
    sock->set_option(option);
    auto conn = std::make_shared<TCPConnection>(sock, OnDisconnected, processIntervalUs);
    conn->Start();
    contextThread = std::thread([this](){
        Run();
    });
    contextThread.detach();
    OnConnected(conn);
    return true;
}

}

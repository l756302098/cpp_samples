/*
 * tcp_connection.h
 *
 *    Created on: Mar 8, 2021
 *            Author: ubuntu
 */

#ifndef TCP_CONNECTION_H_
#define TCP_CONNECTION_H_

#include <iostream>
#include <boost/asio.hpp>
#include <condition_variable>
#include <functional>
#include <list>
#include <thread>
#include "../EffectiveQueue.h"

#include "TLVMessage.h"

namespace trs
{

using boost::asio::ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
    TCPConnection() = default;
public:
    TCPConnection(const TCPConnection&) = default;
    TCPConnection(std::shared_ptr<tcp::socket> sock,
            std::function<void(std::shared_ptr<TCPConnection>)> funcDisconnected,
            std::uint64_t processIntervalUs);

    virtual ~TCPConnection();

    inline void SetOnMessage(std::function<void(std::shared_ptr<TLVMessage>)> funcMessageReceived)
    {
        this->funcMessageReceived = funcMessageReceived;
    }
    void PendMessage(std::shared_ptr<TLVMessage> msg);

    void Start();
    void Stop();

    inline bool IsRunning() { return running; }

private:
    std::function<void(std::shared_ptr<TCPConnection>)> funcDisconnected;
    std::function<void(std::shared_ptr<TLVMessage>)> funcMessageReceived;

    std::shared_ptr<tcp::socket> sock;
    bool running;

    std::mutex mtxSendQueue;
    std::mutex mtxSendQueueNoti;
    std::condition_variable cvSendQueue;
    std::list<std::shared_ptr<TLVMessage>> sendQueue;
    swr::util::EffectiveQueue<std::shared_ptr<TLVMessage>> msgQueue;
    std::thread sendThread;
    std::uint64_t processIntervalUs;

    void OnHeaderReceived(std::shared_ptr<TCPConnection> self, std::shared_ptr<TLVMessage::Header> header,
            boost::system::error_code ec, std::size_t receivedLength);
    void OnBodyReceived(std::shared_ptr<TCPConnection> self, std::shared_ptr<TLVMessage> msg,
            boost::system::error_code ec, std::size_t receivedLength);

    void ReadHeader();
    void ReadBody(std::shared_ptr<TLVMessage::Header> header);

    void Run();

    void Send(std::shared_ptr<TLVMessage>);
    bool Send(std::uint8_t* data, size_t size);
};

}

#endif /* TCP_CONNECTION_H_ */

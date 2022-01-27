/*
 * tcp_service.cpp
 *
 *  Created on: Mar 9, 2021
 *      Author: ubuntu
 */

#include "TCPServer.h"
#include "../Thread.h"

namespace trs
{

TCPServer::TCPServer(
      int port,
      std::function<void(std::shared_ptr<TCPConnection>)> funcConnected,
      std::function<void(std::shared_ptr<TCPConnection>)> funcDisconnected,
      size_t maxConnection,
      std::uint64_t processIntervalUs
      )
{
    currentConnections = 0;
    this->maxConnection = maxConnection;
    this->processIntervalUs = processIntervalUs;
    OnConnected = funcConnected;
    OnDisconnected = funcDisconnected;
    ep = tcp::endpoint(tcp::v4(), port);

    acceptor = std::make_shared<tcp::acceptor>(
            ioContext, ep
    );
}

void TCPServer::Run()  {
    Accept();

    boost::system::error_code ec;
    boost::asio::io_service::work work(ioContext);
    ioContext.run(ec);
}

void TCPServer::Accept()
{
    auto sock = std::make_shared<tcp::socket>(ioContext);
    acceptor->async_accept(*sock, [this, sock](boost::system::error_code ec)
    {
        if (ec == boost::system::errc::success    && currentConnections < maxConnection)
        {
            tcp::no_delay option(true);
            sock->set_option(option);
            ++currentConnections;
            auto connection = std::make_shared<TCPConnection>(
                sock,
                [this](std::shared_ptr<TCPConnection> conn)
                {
                  --currentConnections;
                  OnDisconnected(conn);
                },
                processIntervalUs
            );

            OnConnected(connection);
        }

        Accept();
    });
}

}




#ifndef CLOUD_NODE_H_
#define CLOUD_NODE_H_

#include "tlv/TCPClient.h"
#include "tlv/TCPConnection.h"
#include <thread>
#include <memory>

class CloudNode:std::enable_shared_from_this<CloudNode>
{
private:
    trs::TCPClient* client;
    std::shared_ptr<trs::TCPConnection> conn;
    bool connected;
public:
    CloudNode(/* args */);
    ~CloudNode();
    void Init();
    bool Start();
    void Stop();
    void OnConntected(std::shared_ptr<trs::TCPConnection> conn);
    void OnDisConntected(std::shared_ptr<trs::TCPConnection> conn);
    void OnMessage(std::shared_ptr<trs::TLVMessage> msg);
};

#endif
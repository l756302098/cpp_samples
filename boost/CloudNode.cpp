#include "CloudNode.h"

CloudNode::CloudNode(/* args */)
{
    std::cout << "CloudNode" << std::endl;
}

CloudNode::~CloudNode()
{
    std::cout << "~CloudNode1" << std::endl;
    std::cout << "use_count:" << conn.use_count() << std::endl;
    std::cout << "~CloudNode 2"<< std::endl;
    if (client != nullptr)
    {
        client->Disconnect();
        delete client;
    }
    conn.reset();
    std::cout << "use_count:" << conn.use_count() << std::endl;
    std::cout << "~CloudNode 3"<< std::endl;
}

void CloudNode::Stop()
{
    std::cout << "Stop" << std::endl;
    if (conn != nullptr)
    {
        conn->Stop();
        conn = nullptr;
        std::cout << "use_count:" << conn.use_count() << std::endl;
    }
}

void CloudNode::Init()
{
    client = new trs::TCPClient("192.168.10.150", 6391,
            std::bind(&CloudNode::OnConntected, this, std::placeholders::_1),
            std::bind(&CloudNode::OnDisConntected, this, std::placeholders::_1),
            0);
}
bool CloudNode::Start()
{
     try {
        bool isConnected = client->Connect();
        if(!isConnected){
            std::cout << "tcp client connect server failed.";
            return false;
        }
    }
    catch (...) {
        // do nothing
    }
    return true;
}

void CloudNode::OnConntected(std::shared_ptr<trs::TCPConnection> conn)
{
    std::cout << "Cloud service connected.";
    this->conn = conn;
    conn->SetOnMessage(std::bind(&CloudNode::OnMessage, this, std::placeholders::_1));
    connected = true;
}

void CloudNode::OnDisConntected(std::shared_ptr<trs::TCPConnection> conn)
{
    // report error
    std::cout << "Cloud service dis-connected.";
    connected = false;
    // if (client != nullptr)
    // {
    //     client->Disconnect();
    //     delete client;
    // }
}

void CloudNode::OnMessage(std::shared_ptr<trs::TLVMessage> msg)
{

}
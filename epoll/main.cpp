
#include "tcp_server.h"
#include <thread>
#include <iostream>

abby::TcpServer server;

void sim()
{
    std::cout << "function start..." << std::endl;
    server.Listen();
}

int main(int argc, char* argv[])
{
    
    //server.Listen();
    //start thread
    std::shared_ptr<std::thread> mythread;
    mythread.reset(new std::thread(sim));
    //loop
    while (1)
    {
        sleep(10);
    }

    server.Stop();
    if(mythread && mythread->joinable()) {
        mythread->join();
    }

    return 0;
}
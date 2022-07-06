
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
    std::string first = "mostopic";
    std::string second = "publish";
    std::string third = "house_sweep";
    if(first.compare("mostopic") == 0)
    {
        if(second.compare("publish")==0){
            if(third.compare("house_sweep")==0){
                
                std::cout << "sim publish house_sweep" << std::endl;
            }
            else{
                std::cout << "unsupported topic:" << third<< std::endl;
            }
        }
        else{
            std::cout << "unsupported action:" << second<< std::endl;
        }
    }
    else{
        std::cout << "unsupported types:" << first<< std::endl;
    }
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
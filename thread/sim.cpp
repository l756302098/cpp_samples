#include "sim.h"
#include <iostream>
#include <unistd.h>

sim::sim(/* args */):index(0)
{
}

sim::~sim()
{
}

void sim::Start()
{
    std::cout << "to do 1" << std::endl;
    sleep(5);
    std::unique_lock<std::mutex> lk(mutex);
    std::chrono::duration<int,std::ratio<60> > fiveMint(1);
    auto now = std::chrono::system_clock::now();
    if(condition.wait_until(lk,now + fiveMint ,[&]{
        return index = 1;
    }))
    {
        std::cout << "true ..." << std::endl;
    }
    else
    {
        std::cout << "false ..." << std::endl;
    }
    std::cout << "while finish." << std::endl;
}
    
void sim::Inter()
{
    std::unique_lock<std::mutex> lk(mutex);
    index = 1;
    condition.notify_all();
    std::cout << "notify_all" << std::endl;
}

void sim::Start2()
{
    std::cout << "to do 2" << std::endl;
    std::unique_lock<std::mutex> lk(mutex);
    auto flag = condition.wait_for(lk, std::chrono::seconds(30));
    if(flag == std::cv_status::timeout)
    {
        std::cout << "timeout." << std::endl;
    }
    else
    {
        std::cout << "no timeout." << std::endl;
    }
    
    
}
void sim::Inter2()
{
    std::thread th(&sim::Test2,this);
    th.detach();
}

void sim::Test2()
{
    std::unique_lock<std::mutex> lk(mutex);
    sleep(20);
    condition.notify_all();
    std::cout << "notify_all" << std::endl;
}
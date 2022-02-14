/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include<iostream>
#include<thread>
#include<exception>
#include<stdexcept>

static std::exception_ptr teptr = nullptr;

void sim()
{
    std::cout << "function start..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "throw expection" << std::endl;
    throw std::runtime_error("sim error");
}

int main(int argc, char *argv[])
{
    std::thread mythread(sim);
    mythread.detach();
    while (1)
    {
        std::cout << "main thead sleep." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    
    return 0;
}


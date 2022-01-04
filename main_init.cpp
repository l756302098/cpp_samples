/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include "HzCounter2.h"
#include <unordered_map>

class Counter
{
private:
    /* data */
public:
    Counter(/* args */);
    ~Counter();

    void Add();
};

Counter::Counter(/* args */)
{
}

Counter::~Counter()
{
}

void Counter::Add(){
    std::cout << "add..." << std::endl;
}

std::unordered_map<std::string, swr::util::HzCounter2> watchMap;
std::unordered_map<std::string, Counter> testMap;
 
void test()
{
    while (1)
    {
        usleep(20000);
        std::cout << "thread1 hi hz:" << watchMap["hi"].GetHz() << std::endl;
        std::cout << "thread1 hello hz:" << watchMap["hello"].GetHz() << std::endl;
        auto&& last = watchMap["hi"].SinceLastTick().toMilliseconds();
        if(last > 5 * 1000)
        {   
            std::cout << "main last:" << last << std::endl;
        }
    }
}

int main()  
{  
    //watchMap["hi"].Tick();
    //testMap["li"].Add();
    std::cout << "size:" << watchMap.size() << std::endl;

    std::thread first (test);

    while (1)
    {
        watchMap["hi"].Tick();
        watchMap["hello"].Tick();
        //std::cout << "size:" << watchMap.size() << std::endl;
        std::cout << "hi hz:" << watchMap["hi"].GetHz() << std::endl;
        std::cout << "hello hz:" << watchMap["hello"].GetHz() << std::endl;
        usleep(100000);
    }

    return 0;  
}  

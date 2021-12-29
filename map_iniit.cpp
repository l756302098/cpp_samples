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
#include "HzCounter.h"
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
 
int main()  
{  
    std::unordered_map<std::string, swr::util::HzCounter> watchMap;
    std::unordered_map<std::string, Counter> testMap;

    watchMap["hi"].Tick();
    testMap["li"].Add();
    std::cout << "size:" << watchMap.size() << std::endl;

    while (1)
    {
        watchMap["hi"].Tick();
        watchMap["hello"].Tick();
        std::cout << "size:" << watchMap.size() << std::endl;
        std::cout << "hi hz:" << watchMap["hi"].GetHz() << std::endl;
        std::cout << "hello hz:" << watchMap["hello"].GetHz() << std::endl;
        sleep(1);
    }

    return 0;  
}  

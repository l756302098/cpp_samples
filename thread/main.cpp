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

#include <iostream>
#include "sim.h"
#include "../LoopThread.h"

int main(int argc, char *argv[])
{
    // std::cout << "Start thread demo!" << std::endl;
    // sim simlator;
    // // simlator.Start();

    // // sleep(32);

    // // simlator.Inter();

    // simlator.Inter2();
    
    // simlator.Start2();

    // sleep(66);
    uint32_t second = 3600;
    double rate = 1.0 / second;
    std::cout << "rate:" << rate << std::endl;
    auto loopThread = new swr::util::LoopThread(rate,[](){
        std::cout << "LoopThread Init func." << std::endl;
    },[](){
        std::cout << "LoopThread loop func." << std::endl;
    });
    loopThread->Start();
    
    while (1)
    {
        sleep(1);
    }
    loopThread->Stop();
    
    return 0;
}


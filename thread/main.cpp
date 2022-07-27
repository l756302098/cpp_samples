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

int main(int argc, char *argv[])
{
    std::cout << "Start thread demo!" << std::endl;
    sim simlator;
    // simlator.Start();

    // sleep(32);

    // simlator.Inter();

    simlator.Inter2();
    
    simlator.Start2();

    sleep(66);

    
    
    return 0;
}


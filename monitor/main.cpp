/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>
#include "SystemMonitor.h"

int main(int argc, char *argv[])
{
    SystemMonitor *sm;
    sm = new SystemMonitor();
    sm->Init();
    int counter = 10;
    while (counter > 0)
    {
        sleep(1);
        --counter;
    }
    sm->Stop();
    delete sm;
    return 0;
}


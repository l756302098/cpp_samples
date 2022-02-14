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
    SystemMonitor sm;
    sm.Init();
    while (1)
    {
        sleep(1);
    }
    return 0;
}


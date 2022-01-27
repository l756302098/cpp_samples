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
#include "CloudNode.h"

int main(int argc, char *argv[])
{
    std::cout << "Start boost demo!" << std::endl;

    CloudNode* instance = new CloudNode();
    instance->Init();

    sleep(2);

    instance->Start();

    sleep(5);
    instance->Stop();
    sleep(5);
    delete instance;

    std::cout << "main finish!" << std::endl;
	
    return 0;
}

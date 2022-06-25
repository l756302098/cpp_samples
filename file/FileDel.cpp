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

int main(int argc, char *argv[])
{
    std::cout << "Start clean log!" << std::endl;

    std::string cmd = "find /home/li/log/0621log/log -type f -mtime +2 -exec rm -f {} \\;";
	int result = system(cmd.c_str());
	if(result==0)
	{
		std::cout << "clean log success!" << std::endl;
	}

    return 0;
}

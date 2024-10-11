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
#include <fstream>
#include "YamlDemo.h"
#include "../FilePath.h"
#include "DDSConfig.h"

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    //wk::ROS_DOMAIN_ID = 1;
    yaml::demo::YamlDemo demo;
    std::cout << "ROS_DOMAIN_ID:" << wk::ROS_DOMAIN_ID << std::endl;
    //demo.TestAdd();
    //demo.TestAdd();
    demo.TestRead();
    std::cout << "ROS_DOMAIN_ID:" << wk::ROS_DOMAIN_ID << std::endl;
    demo.SimUpdateYaml();
    std::cout << "ROS_DOMAIN_ID:" << wk::ROS_DOMAIN_ID << std::endl;
    return 0;
}


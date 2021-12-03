/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <iostream>
#include "YamlDemo.h"

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    yaml::demo::YamlDemo demo;
    demo.ReadAndWriteYaml();
    demo.SaveToYaml();
    demo.ReadAndWriteYaml();

    return 0;
}

/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>
#include "../FilePath.h"
#include "SystemHelper.h"
#include "../StringHelper.h"

int main(int argc, char *argv[])
{
    // char *cmd = new char[128];
    // sprintf(cmd,"mount | grep -a '%s' | wc -l",'/media/li');
    // std::string cmd  = "mount | grep -a '/mnt/upgrades' | wc -l";

    int result = system("cd /root/workspace/client/ && ./updater.sh /mnt/upgrades VCU");
    std::cout  << "result 0:" << result << std::endl;

    float d = 4.6111;
    int16_t temp = d * 10;
    std::cout  << "temp:" << temp << std::endl;

    d = -4.6111;
    temp = d * 10;
    std::cout  << "temp:" << temp << std::endl;

    // std::string cmd = "./updater.sh /mnt/upgrades VCU";;
    // std::cout  << "cmd:" << cmd << std::endl;
    // result = system(cmd.c_str());
    // std::cout << "result 1:" << result << std::endl;
    // result = system("cd -");
    // std::cout << "result 2:" << result << std::endl;

    // std::string cmd = "mount | grep -a '/media/li' | wc -l";
    // std::cout << "cmd:" << cmd << std::endl;
    // char resultBuf[16];
    // auto result = SystemHelper::get_cmd_results(cmd.c_str(),resultBuf,16);
    // if (result < 0)
    // {
    //     std::cout << "get mount failed." << result << std::endl;
    //     return -1;
    // }
    // std::string resultStr(&resultBuf[0],&resultBuf[strlen(resultBuf)]);
    // std::cout << "resultStr:" << resultStr << std::endl;
    // if(resultStr.find("1") != std::string::npos)
    // {
    //     std::cout << "contains 1"<< std::endl;
    // }
    // else
    // {
    //     std::cout << "not contains 1"<< std::endl;
    // }

    //Test1
    {
        std::string packageDir = "/mnt/upgrades/INDEMINDAPP_I18R_MP-SIGN_1.1.79.4.deb";
        std::size_t found = packageDir.find_last_of('/');
        std::string filePath = packageDir.substr(0,found);
        std::string package = packageDir.substr(found+1);

        std::size_t foundD = package.find_last_of('.');
        std::string noSuffix = package.substr(0,foundD);
        std::size_t foundL = noSuffix.find_last_of('_');
        std::string version = noSuffix.substr(foundL+1);
        std::cout << "filePath:" << filePath << " package:" << package 
                << " version:" << version << std::endl;
    }

    //test2
    {
        std::string current_package_name = "INDEMINDAPP_I18R_MP-SIGN_1.1.79.4.deb";
        std::size_t foundD = current_package_name.find_last_of('.');
        std::string noSuffix = current_package_name.substr(0,foundD);
        std::size_t foundL = noSuffix.find_last_of('_');
        std::string version = noSuffix.substr(foundL+1);
        std::cout << "version:" << version << std::endl;
    }

    //test3
    {
        std::string package = "INDEMINDAPP_I18R_MP-SIGN_1.1.79.4.deb";
        std::size_t foundD = package.find_last_of('.');
        std::string noSuffix = package.substr(0,foundD);
        std::size_t foundL = noSuffix.find_last_of('_');
        std::string currentVersion = noSuffix.substr(foundL+1);
        
        //calc
        std::vector<std::string> splits = swr::util::StringHelper::Split(currentVersion,'.');
        int result = 0;
        if(splits.size() == 4)
        {
            int major = stoi(splits[0]);
            int minor = stoi(splits[1]);
            int patch = stoi(splits[2]);
            int end = stoi(splits[3]);
            std::cout << "major:" << major << " minor:" << minor
            << " patch:" << patch << " end:" << end << std::endl;
            result = major * 100000 + minor * 10000 + patch * 100 + end;
        }

        std::cout << "allName:" << package << " version:" << currentVersion
            << " result:" << result << std::endl;
    }

    return 0;
}


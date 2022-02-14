/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>
#include "../FilePath.h"

int main(int argc, char *argv[])
{
    std::string fileDir = "/home/li/map/routes/100/0";
    std::string routeCode = "1c43931d229541cf8b72b4a38551133d";
    std::string filePath = fileDir + "/" + routeCode + "/";
    std::string targetFile = routeCode+".tar.gz";
    std::string mapFile = routeCode+".map";
    std::string mapBinFile = routeCode+".map.bin";
    std::cout << "monitor disk" << std::endl;
    std::string cdCmd = "cd " + filePath;
    printf("cmd: %s \n",cdCmd.c_str());
    char cmdBuf[120];
    sprintf(cmdBuf, "%s && tar -zcvf %s %s %s",cdCmd.c_str(),targetFile.c_str(),mapFile.c_str(),mapBinFile.c_str());
    printf("cmd: %s \n",cmdBuf);
    auto result = system(cmdBuf);
    if (result != 0)
    {
        std::cout << "tar compress faile." << std::endl;
    }
    //rename


    //unpack
    memset(cmdBuf,0x0,120);
    sprintf(cmdBuf, "%s && tar zxvf %s",cdCmd.c_str(),targetFile.c_str());
    printf("cmd: %s \n",cmdBuf);
    result = system(cmdBuf);
    if (result != 0)
    {
        std::cout << "uncompress failed." << std::endl;
    }
    return 0;
}


/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <sys/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <memory>

std::string subreplace(const std::string& resource_str,const std::string& sub_str,const std::string& new_str)
{
    std::string dst_str = resource_str;
    std::string::size_type pos = 0;
    while((pos = dst_str.find(sub_str)) != std::string::npos)
    {
        std::cout << "replace " << pos << " " << sub_str.length() << std::endl;
        dst_str.replace(pos, sub_str.length(), new_str);
    }
    return dst_str;
}

int main(int argc, char *argv[])
{
    std::cout << "monitor disk" << std::endl;
    
    std::string localNfsPath = "/app/share/map/routes/";
    std::string nfsPath = "/home/tan/project/share";
    std::string newStr = subreplace(localNfsPath,"/app/share",nfsPath);

    std::cout << "localNfsPath:" << newStr << std::endl;

    return 0;
}


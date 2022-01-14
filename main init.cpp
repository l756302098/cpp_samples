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

#include <iostream>
#include "FilePath.h"



int main(int argc, char *argv[])
{
    std::cout << "monitor disk" << std::endl;
    /*
    struct statfs diskInfo;
    std::string exePath = swr::util::FilePath::GetCurExePath();
    statfs(exePath.c_str(), &diskInfo);
    auto totalBlocks = diskInfo.f_bsize;
    auto freeDisk = diskInfo.f_bfree * totalBlocks;
    std::cout << "Free disk size: " << freeDisk / 1024 / 1024 / 1024 << "GB";
    */
    float time1 = 5 * 1e-6;
    float time2 = 5 * 1e6;
    printf("%f %f \n",time1,time2);

    std::string aa;
    int a;
    float b;
    double c;
    char cc;

    printf("int a = %d \n",a);
    printf("float b = %f \n",b);
    printf("double c = %f \n",c);
    printf("char cc = %c \n",cc);
    printf("string aa = %s \n",aa);

    return 0;
}


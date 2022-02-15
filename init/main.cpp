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
#include <string.h>

struct RouteInfo {
    std::string siteCode;
    std::string hlcCode;
    uint8_t     slotCode;
    uint64_t    mapId;
    std::string routeCode;
    uint8_t     model;          //工作模式 0x00-轨迹 0x01-边界弓型 0x02-边界回型 0xFF：无效
    std::string mapPath;        //绝对路径
    std::string pngPath;
    std::string routePath;
    std::string semanticPath;
    uint8_t     mapState;       //0x01 本地 0x10云端 0x11本地云端皆在
    uint8_t     pngState;
    uint8_t     routeState;
    uint8_t     configState;
    std::string bodyNum;        //机身号
    std::string machineName;    //机器自定义名称
    std::string routeName;      //用户自定义路径名称
    uint32_t    size;           //文件大小
    uint32_t    time;           //地图生成时间UTC
    bool enableVirtualWall;
};

int main(int argc, char *argv[])
{
    // std::cout << "monitor disk" << std::endl;
    // float time1 = 5 * 1e-6;
    // float time2 = 5 * 1e6;
    // printf("%f %f \n",time1,time2);

    // std::string aa;
    // int a;
    // float b;
    // double c;
    // char cc;

    // printf("int a = %d \n",a);
    // printf("float b = %f \n",b);
    // printf("double c = %f \n",c);
    // printf("char cc = %c \n",cc);
    // printf("string aa = %s \n",aa);

    RouteInfo ri;
    memset(&ri,0,sizeof(RouteInfo));
    printf("int png path = %s state = %d \n",ri.pngPath.c_str(),ri.pngState);
    printf("int map state = %d \n",ri.mapState);
    printf("int route state = %d \n",ri.routeState);
    printf("int config state = %d \n",ri.configState);

    std::cout << "" << ri.routePath << " " << ri.routePath.empty() << std::endl;

    return 0;
}


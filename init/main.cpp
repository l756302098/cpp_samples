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

    // RouteInfo ri;
    // //memset(&ri,0,sizeof(RouteInfo));
    // printf("int png path = %s state = %d \n",ri.pngPath.c_str(),ri.pngState);
    // printf("int map state = %d \n",ri.mapState);
    // printf("int route state = %d \n",ri.routeState);
    // printf("int config state = %d \n",ri.configState);

    // std::cout << "" << ri.routePath << " " << ri.routePath.empty() << std::endl;
    // memset(&ri,0,sizeof(RouteInfo));

    // std::string a;
    // memset(&a,0,sizeof(std::string));
    // std::cout << "a:" << a;
    // a = "123";
    // std::cout << "size:" << a.size();
    // RouteInfo ri1;
    // memset(&ri1,0,sizeof(RouteInfo));
    // printf("int png path = %s state = %d \n",ri1.pngPath.c_str(),ri1.pngState);
    // std::cout << "empty:" << ri.pngPath.empty() << " " << ri.pngPath << std::endl;
    // std::cout << "empty:" << ri1.pngPath.empty() << " " << ri1.pngPath << std::endl;
    // ri1.pngPath = ri.pngPath.empty() ? "" : ri.pngPath;
    // printf("int png path = %s state = %d \n",ri1.pngPath.c_str(),ri1.pngState);
    // printf("int map state = %d \n",ri1.mapState);
    // printf("int route state = %d \n",ri1.routeState);
    // printf("int config state = %d \n",ri1.configState);

    // std::string a,b;
    // printf("a = %s b = %s \n",a.c_str(),b.c_str());
    // memset(&a,0,sizeof(std::string));
    // printf("a = %s b = %s \n",a.c_str(),b.c_str());
    // b = a;
    // printf("a = %s b = %s \n",a.c_str(),b.c_str());
    // std::cout << "a:" << a << std::endl;

    // int c,d;
    // printf("c = %i,d = %i",c,d);
    // c = 0;
    // d = 0;
    // printf("c++ = %i,++d = %i",c++,++d);

    if(-1)
    {
        std::cout << " -1 is true.";
    }
    else{
        std::cout << " -1 is false.";
    }

    //std::string package_name = "INDEMINDAPP_I18R_EVT2_INTG_1.0.17_1.0.14.tgz";
    std::string package_name = "INDEMINDAPP_DVT_0627.deb";

    // 获取版本号
    auto rdot_1 = package_name.rfind('.');
    if(std::string::npos == rdot_1) return false;
    auto split_pos = package_name.rfind('_');
    auto all_name = package_name.substr(split_pos + 1, package_name.length() - split_pos - 5);
    std::cout << "get version success.  all_name:" << all_name << std::endl;

    auto rdot_2 = package_name.rfind('.', rdot_1 - 1);
    if(std::string::npos == rdot_2) return false;
    auto rdot_3 = package_name.rfind('.', rdot_2 - 1);
    if(std::string::npos == rdot_3) return false;

    // 获取完整名称
    

    auto hi_str = package_name.substr(rdot_3 + 1, rdot_2 - rdot_3 - 1);
    auto lo_str = package_name.substr(rdot_2 + 1, rdot_1 - rdot_2 - 1);
    

    std::cout << "rdot_1:" << rdot_1 << " "<<package_name.length() << std::endl;
    std::cout << "get version success. hi: " << hi_str << ", lo: " << lo_str << " all_name:" << all_name << std::endl;

    return 0;
}


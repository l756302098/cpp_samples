/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>
#include <glog/logging.h>
#include <iostream>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system_helper.h"

#include <thread>
#include <memory>

int PublishIp2()
{
 std::string ssid{""};
        std::string ip{""};
        //get ipv4
        struct ifaddrs *interfaces = nullptr;
        struct ifaddrs *addr = nullptr;
        int result = getifaddrs(&interfaces);
        if (result == 0) {
            for (addr = interfaces; addr != nullptr; addr = addr->ifa_next) {
                if (addr->ifa_addr && addr->ifa_addr->sa_family == AF_INET) { // IPv4
                    struct sockaddr_in *ipAddr = reinterpret_cast<struct sockaddr_in *>(addr->ifa_addr);
                    //LOG(INFO) << "ipv4 "<< addr->ifa_name << ": " << inet_ntoa(ipAddr->sin_addr);
                    std::string ifa = addr->ifa_name;
                    if(ifa.compare(0,2,"wl")==0)
                    {
                        ip = inet_ntoa(ipAddr->sin_addr);
                        LOG_EVERY_N(INFO, 10) << "current ipv4:"<< ip;
                    }
                } 
                // else if (addr->ifa_addr && addr->ifa_addr->sa_family == AF_INET6) { // IPv6
                //     struct sockaddr_in6 *ipAddr = reinterpret_cast<struct sockaddr_in6 *>(addr->ifa_addr);
                //     char ipStr[INET6_ADDRSTRLEN];
                //     inet_ntop(AF_INET6, &ipAddr->sin6_addr, ipStr, INET6_ADDRSTRLEN);
                //     LOG(INFO) << "ipv6 " << addr->ifa_name << ": " << ipStr;
                // }
            }
            freeifaddrs(interfaces);
        } else {
            ip = "";
            LOG(ERROR) << "getifaddrs failed with error: " << result;
            return 0;
        }
        //get ssid
        std::string cmd{"iwgetid"};
        char buffer[128] = {};
        if(wk::SystemHelper::get_cmd_results(cmd.c_str(),buffer,128) < 0)
        {
            LOG(ERROR) << "call system timeout.";
        }
        else
        {
            //LOG(INFO) << "rece buffer:" << buffer;
            std::string wgetStr(&buffer[0],&buffer[strlen(buffer)]);
            
        }

}

int PublishIp()
{
    std::string ssid{""};
    std::string ip{""};
    //get ipv4
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *addr = nullptr;
    int result = getifaddrs(&interfaces);
    if (result == 0) {
        for (addr = interfaces; addr != nullptr; addr = addr->ifa_next) {
            if (addr->ifa_addr && addr->ifa_addr->sa_family == AF_INET) { // IPv4
                struct sockaddr_in *ipAddr = reinterpret_cast<struct sockaddr_in *>(addr->ifa_addr);
                LOG(INFO) << "ipv4 "<< addr->ifa_name << ": " << inet_ntoa(ipAddr->sin_addr);
                std::string ifa = addr->ifa_name;
                if(ifa.compare(0,2,"wl")==0)
                {
                    ip = inet_ntoa(ipAddr->sin_addr);
                    LOG_EVERY_N(INFO, 10) << "current ipv4:"<< ip;
                }
            } 
            // else if (addr->ifa_addr && addr->ifa_addr->sa_family == AF_INET6) { // IPv6
            //     struct sockaddr_in6 *ipAddr = reinterpret_cast<struct sockaddr_in6 *>(addr->ifa_addr);
            //     char ipStr[INET6_ADDRSTRLEN];
            //     inet_ntop(AF_INET6, &ipAddr->sin6_addr, ipStr, INET6_ADDRSTRLEN);
            //     LOG(INFO) << "ipv6 " << addr->ifa_name << ": " << ipStr;
            // }
        }
        freeifaddrs(interfaces);
    } else {
        ip = "";
        LOG(ERROR) << "getifaddrs failed with error: " << result;
        return 0;
    }
    //get ssid
    FILE *fp;
    char path[1035];
    char wifi_name[32];
    // 执行iw命令获取当前连接的WiFi名称
    strcpy(path, "iwgetid | grep 'SSID' | awk -F ':' '{print $2}' ");
    // 打开管道，读取命令的输出
    fp = popen(path, "r");
    if (fp != NULL) {
        LOG(INFO) << "open fp success.\n";
        // 读取WiFi名称
        while (fgets(wifi_name, sizeof(wifi_name), fp) != NULL) {
            // 去除可能的换行符
            wifi_name[strcspn(wifi_name, "\n")] = 0;
            LOG(INFO) << "Connected WiFi:" << wifi_name;
            break; // 只获取第一行，因为我们只关心当前连接的WiFi
        }
        pclose(fp);
    }
}

void InitCheck()
{
    while (1)
    {
        PublishIp();
        sleep(1);
        PublishIp2();
    }
}

int main(int argc, char *argv[])
{
    
    std::thread t2(InitCheck);
    t2.detach();

    getchar();
    return 0;
}


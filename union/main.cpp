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

#include <thread>
#include <memory>

union S
{ 
    std:: int32_t n ;           // 占用 4 个字节
    std:: uint16_t s [ 2 ] ;    // 占用 4 个字节
    std:: uint8_t c ;           // 占用 1 个字节
} ; 

int main(int argc, char *argv[])
{
    S s{0x12345678};
    std::cout  <<  std::hex << "s.n:" << s.n << std::endl;
    std::cout << "s.s:" << s.s[0] << " " << s.s[1]  << std::endl;
    std::cout << "s size:" << sizeof(s) << std::endl;
    getchar();
    return 0;
}


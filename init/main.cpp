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



int main(int argc, char *argv[])
{
    std::cout << "monitor disk" << std::endl;
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


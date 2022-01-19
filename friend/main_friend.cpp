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
#include <memory>
#include "StudentB.hpp"

class A
{
    friend class B;
private:
    std::string name;
    bool PrintName(){
        std::cout << "A name:" << name << std::endl;
    }
public:
    A(/* args */){}
    ~A(){}
};

class B : public std::enable_shared_from_this<B> 
{
public:
    B(/* args */){}
    ~B(){}
    void PrintA()
    {
        A a;
        a.name = "test";
        a.PrintName();
    }
};


int main(int argc, char *argv[])
{
    std::cout << "monitor disk" << std::endl;
    // B b;
    // b.PrintA();

    aa::bbb::StudentB b;
    b.Print();

    return 0;
}


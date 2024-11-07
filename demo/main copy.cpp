/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>

class A
{
public:
    int a;
    void print(){
        std::cout << "print result." << std::endl;
    }
};


class B
{
private:
    /* data */
public:
    B(/* args */)
    {
        std::cout << "default construction." << std::endl;
    }
    B(const B& d)
    {
        std::cout << "copy construction." << std::endl;
    }
    B(B&& d)
    {
        std::cout << "move construction." << std::endl;
    }
    ~B()
    {}
};



int main(int argc, char *argv[])
{
    // A* a = 0;
    // a->print();
    // std::cout << "size:" << sizeof(A) << std::endl;

    // B b;
    // B b1 = b;
    // B b2(b);
    // B b3(std::move(b));

    int a = 0;
    int b = 0;
    int a1 =  a++;
    int b1 = ++b;
    std::cout << "a:" << a1 << " b:" << b1 << std::endl;

    return 0;
}


/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>
#include <list>

int main(int argc, char *argv[])
{
    std::list<int> first;
    first.emplace_back(1);
    first.emplace_back(2);
    first.emplace_back(3);
    first.emplace_back(4);
    first.emplace_back(5);
    first.emplace_back(6);
    first.emplace_back(7);
    first.emplace_back(8);


    for (std::list<int>::iterator it=first.begin(); it!=first.end();)
    {
        
        if(*it == 5)
        {
            first.erase(it++);
            //it++;
        }
        else{
            ++it;
        }
    }

    for (std::list<int>::iterator it=first.begin(); it!=first.end(); ++it)
    {
        std::cout << "value:" << *it << std::endl;
    }
    

    return 0;
}


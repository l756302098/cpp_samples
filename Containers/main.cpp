/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <iostream>
#include <list>
#include <unordered_map>
#include <functional>

std::list<int> dlist;

int main ()
{
    std::unordered_map<int,std::string> filter_map;
    for (size_t i = 0; i < 20; i++)
    {
        filter_map.emplace(std::make_pair(i,""));
    }
    
    for (size_t i = 0; i < 100; i++)
    {
        dlist.emplace_back(i);
    }

    dlist.remove_if([&filter_map](const int &value)->bool{
        if(filter_map.find(value)==filter_map.end())
        {
            std::cout << "remove value:" << value << std::endl;
            return true;
        }
        return false;
    });
    std::cout << "count:" << dlist.size() << std::endl;
    return 0;
}


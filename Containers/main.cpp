/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <iostream>
#include <list>
#include <functional>

struct Map
{
    int id;
    std::uint32_t time;
};


class MapManager
{
public:
    MapManager();
    ~MapManager();
    bool CompareRoute(const Map& first, const Map& second);
    void Test();
};

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}

bool MapManager::CompareRoute(const Map& first, const Map& second)
{
    if(first.time < second.time)
    {
        return true;
    }
    return false;
}

void MapManager::Test()
{
    std::list<Map> mapList;
    Map map1;
    map1.id = 1;
    map1.time = 1000;
    mapList.push_back(map1);
    Map map2;
    map2.id = 2;
    map2.time = 1001;
    mapList.push_back(map2);
    Map map3;
    map3.id = 3;
    map3.time = 666;
    mapList.push_back(map3);
    for (auto &&item : mapList)
    {   
        std::cout << item.id << " " << item.time << std::endl; 
    }
    mapList.sort([](const Map& first, const Map& second)->bool{
        if(first.time < second.time)
        {
            return true;
        }
        return false;
    });
    std::cout << "----------------" << std::endl; 
    for (auto &&item : mapList)
    {   
        std::cout << item.id << " " << item.time << std::endl; 
    }
}


int main ()
{
    MapManager mm;
    mm.Test();
    return 0;
}


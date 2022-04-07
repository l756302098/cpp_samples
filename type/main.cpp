/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "Person.h"
#include "Teacher.h"


struct TaskItem
{
    std::uint16_t   operation;
    std::int16_t    resType;
    virtual void Show(){}
};

struct MapItem : public TaskItem
{
    int map;
    void Show(){}
};

struct FirmwareItem : public TaskItem
{   
   	int firmware;
    void Show(){}
};


int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    
	// Person p;
	// Teacher tc;
	// std::string pName = typeid(p).name();
	// std::string tcName = typeid(tc).name();
	// std::string::size_type idx1 = tcName.find("Teacher");
	// if(idx1 != std::string::npos){
	// 	std::cout << "this is Teacher" << std::endl;
	// }
    // std::cout << "pName:" << pName << " tcName:" << tcName << std::endl;
	FirmwareItem fi;
	fi.firmware = 1;
	TaskItem& ti = fi;
	FirmwareItem& item = dynamic_cast<FirmwareItem&>(ti);
	std::cout << "firmware int " << item.firmware << std::endl;

	MapItem mi;
	mi.map = 11;
	TaskItem* ti1 = &mi;
	MapItem* item1 = dynamic_cast<MapItem*>(ti1);
	std::cout << "firmware int " << item1->map << std::endl;

    return 0;
}

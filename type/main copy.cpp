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
#include <list>
#include <memory>

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

class MyClass
{
public:
  MyClass()
  {
    std::cout << "调用默认构造函数" << std::endl;
  }
  MyClass(const MyClass& a) 
  {
    std::cout << "调用拷贝构造函数" << std::endl;
  }
  ~MyClass(){}
};

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    
	Person p;
	Teacher tc;
	std::string pName = typeid(p).name();
	std::string tcName = typeid(tc).name();
	std::string::size_type idx1 = tcName.find("Teacher");
	if(idx1 != std::string::npos){
		std::cout << "this is Teacher" << std::endl;
	}
    std::cout << "pName:" << pName << " tcName:" << tcName << std::endl;
	FirmwareItem fi;
	fi.firmware = 1;
	TaskItem& ti = fi;
	FirmwareItem& item = dynamic_cast<FirmwareItem&>(ti);
	std::cout << "firmware int " << item.firmware << std::endl;

	std::shared_ptr<MapItem> mi;
	std::shared_ptr<TaskItem> tmi;
	tmi = mi;
	std::shared_ptr<FirmwareItem> tmiPtr = std::dynamic_pointer_cast<FirmwareItem>(tmi);
	if(tmiPtr==nullptr)
	{
		std::cout << "tmiPtr is null."<< std::endl;
	}

	// MapItem mi;
	// mi.map = 11;
	// TaskItem* ti1 = &mi;
	// MapItem* item1 = dynamic_cast<MapItem*>(ti1);
	// std::cout << "firmware int " << item1->map << std::endl;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	std::cout << "i:" << i << std::endl;
	// 	for (size_t j = 0; j < 10; j++)
	// 	{
	// 		std::cout << "j:" << j << std::endl;
	// 		for (size_t k = 0; k < 5; k++)
	// 		{
	// 			std::cout << "k:" << k << std::endl;
	// 			if(k==1)
	// 			{
	// 				std::cout << "break:" << k << std::endl;
	// 				break;
	// 			}
	// 		}
			
	// 	}
		
	// }


	// std::list<int> list;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	list.emplace_back(i);
	// }
	// std::cout << "del index 3." << std::endl;
	// for (auto it = list.begin();it!=list.end();)
	// {
	// 	if(*it ==3)
	// 	{
	// 		list.erase(it++);
	// 		std::cout << "+++++++++++++" << std::endl;
	// 	}
	// 	else{
	// 		++it;
	// 	}
	// }
	// std::cout << "print result:" <<  list.size() << std::endl;
	// for (auto it = list.begin();it!=list.end();it++)
	// {
	// 	std::cout << " " << *it << std::endl;
	// }
	
	// std::string cmd = "mv /home/li/kb.log /home/li/log/kb.log";
	// int ret = system(cmd.c_str());
	// std::cout << "ret:" << ret << std::endl;
	// if(ret==0)
	// {
	// 	std::cout << "Wait for the next boot upgrade.";
	// }
	// else{
	// 	std::cout << "move file failed. ";
	// }

    return 0;
}

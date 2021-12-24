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
#include "YamlDemo.h"
#include "FilePath.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"

struct HlcInfo
{
	std::string name;
	std::int16_t age;
};


void MoveFile(){
    std::string targetPath = "/home/li/info.yaml";
    std::string nfsPath  = "/home/li/log/test";
    if(!swr::util::FilePath::IsDirExisted(nfsPath)){
        swr::util::FilePath::CreateDir(nfsPath.c_str());
    }
    nfsPath = nfsPath + "/info.yaml";
    bool isSave = swr::util::FilePath::CopyFile(targetPath.c_str(),nfsPath.c_str());
    if(!isSave){
        std::cout << "save failed" << std::endl;
    }
    int size = swr::util::FilePath::GetFileSize(nfsPath.c_str());
    std::cout << "file size:" << size << std::endl;
}

void LoopDemo(){
	std::cout << "start loop" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "i:" << i << std::endl;
		for (int j = 0; j < 10; j++)
		{
			std::cout << "j:" << j << std::endl;
			if(j==5)
			{
				std::cout << "break" << std::endl;
				break;
			}
		}
	}
	std::cout << "end loop" << std::endl;
}

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    yaml::demo::YamlDemo demo;
    demo.ReadAndWriteYaml();
    demo.SaveToYaml();
    demo.ReadAndWriteYaml();
    demo.DelYaml2();
    // MoveFile();

	// LoopDemo();

	// HlcInfo info;
	// std::cout << info.name << " isempty:" << info.name.empty() << " size:" << info.name.size() << " " << info.age << std::endl;
    return 0;
}

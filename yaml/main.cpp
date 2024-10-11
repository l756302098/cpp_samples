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
#include <fstream>
#include "YamlDemo.h"
#include "../FilePath.h"

struct HlcInfo
{
	std::string name;
	std::int16_t age;
};


void CopyFile(){
    YAML::Node cloneNode;
    if(!cloneNode.IsNull())
    {
        std::string bodyNum = cloneNode["bodyNum2"].as<std::string>();
        std::cout << "bodyNum:" << bodyNum << std::endl;
    }
    else
    {
        std::cout <<"cloneNode is defined."<< std::endl;
    }
    std::string targetPath = "/home/li/workspaces/SmallWashingRobotSDK/config/cloud/config.yaml";
    if (!swr::util::FilePath::IsFileExisted(targetPath))
    {
        std::cout <<"No configure file found." << targetPath << std::endl;
        return;
    }
    YAML::Node config = YAML::LoadFile(targetPath);
    cloneNode = YAML::Clone(config);
    if(cloneNode.IsMap())
    {
        std::cout <<"cloneNode is defined."<< std::endl;
        std::string bodyNum = cloneNode["bodyNum2"].as<std::string>();
        std::cout << "bodyNum:" << bodyNum << std::endl;
    }
    
}

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

bool UpadteConfig(const std::string& lastDate)
{
    std::string filepath = "/home/li/log_config.yaml";

    //read config
    try
    {
        YAML::Node config = YAML::LoadFile(filepath);
        config["last_time"] = lastDate;
        std::cout << "update last_time:" << lastDate << std::endl;
        //write new conf
        std::ofstream fout(filepath);
        fout << config;
        fout.close();
    }
    catch(...)
    {
        std::cout  << "config.json parse failed." << filepath << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    //CopyFile();
    //UpadteConfig("1");
    yaml::demo::YamlDemo demo;
    long id = long(&demo);
    std::cout << "id:" << id << std::endl;
    //demo.TestAdd();
    //demo.TestAdd();
    demo.TestRead();
    demo.SimUpdateYaml();
    return 0;
}


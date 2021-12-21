/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <iostream>
#include "YamlDemo.h"
#include "FilePath.h"

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

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    yaml::demo::YamlDemo demo;
    // demo.ReadAndWriteYaml();
    // demo.SaveToYaml();
    // demo.ReadAndWriteYaml();
    demo.DelYaml();
    // MoveFile();

    return 0;
}

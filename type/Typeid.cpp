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

void LockSet(int fd, int type) {
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	while (1) {
		lock.l_type = type;
		if ((fcntl(fd, F_SETLK, &lock)) == 0) {
			if (lock.l_type == F_RDLCK)
				printf("read lock set by %d\n", getpid());
			else if(lock.l_type == F_WRLCK)
				printf("write lock set by %d\n", getpid());
			else if (lock.l_type == F_UNLCK)
				printf("release lock by %d\n", getpid());
			return;
		}
		//检查文件是否可以上锁
		fcntl(fd, F_GETLK, &lock);
		//判断不能上锁的原因
		if (lock.l_type != F_UNLCK) {
			if (lock.l_type == F_RDLCK)
				printf("read lock has been already set by %d\n", getpid());
			else if (lock.l_type == F_WRLCK)
			printf("write lock has been already set by %d\n", getpid());
			getchar();
		}
	}
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
    
	Person p;
	Student st;
	Teacher tc;
	std::string pName = typeid(p).name();
	std::string stName = typeid(st).name();
	std::string tcName = typeid(tc).name();
	std::string::size_type idx = stName.find("Student");
	if(idx != std::string::npos){
		std::cout << "this is Student" << std::endl;
	}
	std::string::size_type idx1 = stName.find("Teacher");
	if(idx1 != std::string::npos){
		std::cout << "this is Teacher" << std::endl;
	}
    std::cout << "pName:" << pName << " stName:" << stName << " tcName:" << tcName << std::endl;
	
    return 0;
}

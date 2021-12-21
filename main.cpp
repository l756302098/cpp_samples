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

int main(int argc, char *argv[])
{
    std::cout << "Start yaml demo!" << std::endl;
    //yaml::demo::YamlDemo demo;
    // demo.ReadAndWriteYaml();
    // demo.SaveToYaml();
    // demo.ReadAndWriteYaml();
    // demo.DelYaml();
    // MoveFile();

    int fd;
	fd = open("/home/li/info.yaml", O_RDWR | O_CREAT, 0666);
	if (fd < 0) {
		perror("open failed");
		return -1;
	}
	LockSet(fd, F_WRLCK);
	getchar();
	LockSet(fd, F_UNLCK);
	getchar();
	close(fd);

    return 0;
}

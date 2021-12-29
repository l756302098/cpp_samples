/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "FilePath.h"

void SplitFile(){
	//split image into 10 parts
	std::string targetPath = "/home/li/Documents/d0c50-linux2bfile2bsystem2bhierarchy.jpg";
	
	FILE *fp;
	/* 打开文件用于读写 */
	fp = fopen(targetPath.c_str(), "r+");
	//将文件指针移动文件结尾
	fseek (fp, 0, SEEK_END);
	//求出当前文件指针距离文件开始的字节数 	
 	size_t size= ftell(fp);
	std::cout << "file size:" << size << " size(kb):" << (size/1024) << std::endl;
	
	fseek(fp, 0, SEEK_SET);
	char *buf = new char[size]; 
    memset(buf,0x0,size);
	fread(buf, size, 1, fp);

	fclose(fp);	

	int unitSize = size / 10;
	int childCount = size % unitSize == 0 ? size / unitSize : size / unitSize + 1;
	std::cout << "unitSize:" << unitSize << " childCount:" << childCount << std::endl;
	std::string rootPath = "/home/li/Documents/Test/";
	for (size_t i = 0; i < childCount; i++)
	{
		std::string childPath = rootPath + std::to_string(i);
		FILE *cfp;
		/* 打开文件用于读写 */
		cfp = fopen(childPath.c_str(), "w+");
		/* 写入数据到文件 */
		fwrite(buf + i * unitSize, unitSize, 1, cfp);
		fclose(cfp);
	}
	delete buf;
}

void MergeFile(){
	size_t total = 60750;
	size_t unitSize = total / 10;
	char *buf = new char[total]; 
    memset(buf,0x0,total);
	std::string rootPath = "/home/li/Documents/Test/";
	for (size_t i = 0; i < 10; i++)
	{
		std::string childPath = rootPath + std::to_string(i);
		FILE *cfp;
		/* 打开文件用于读写 */
		cfp = fopen(childPath.c_str(), "r+");
		/* 写入数据到文件 */
		fread(buf + i * unitSize, unitSize, 1, cfp);
		fclose(cfp);
	}
	FILE *fp;
	std::string targetPath = rootPath + "ori.jpg";
	/* 打开文件用于读写 */
	fp = fopen(targetPath.c_str(), "w+");
	/* 写入数据到文件 */
	fwrite(buf, total, 1, fp);
	fclose(fp);
	delete buf;
}

void MergeFile2(){
	//get total size
	std::string totalBuf;
	size_t totalSize = 0;
	std::string rootPath = "/home/li/Documents/Test/";
	for (size_t i = 0; i < 10; i++)
	{
		std::string childPath = rootPath + std::to_string(i);
		size_t fileSize = swr::util::FilePath::GetFileSize(childPath.c_str());
		if(fileSize != -1)
		{
			totalSize += fileSize;
		}
		char *buf = new char[fileSize];
    	memset(buf,0x0,fileSize);
		FILE *cfp;
		/* 打开文件用于读写 */
		cfp = fopen(childPath.c_str(), "r+");
		/* 写入数据到文件 */
		size_t readSize = fread(buf, fileSize, 1, cfp);
		std::cout << "fileSize:" << fileSize << " readSize:" << readSize <<std::endl;
		//fclose(cfp);
		std::string str(buf);
		//str.assign(&buf[0],&buf[strlen(buf)]);
		totalBuf += str;
		delete buf;
	}
	FILE *fp;
	std::string targetPath = rootPath + "ori.jpg";
	/* 打开文件用于读写 */
	fp = fopen(targetPath.c_str(), "w+");
	/* 写入数据到文件 */
	fwrite(totalBuf.c_str(), totalSize, 1, fp);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	SplitFile();
	MergeFile2();
	{
		FILE *fp;
		char c[] = "This is runoob";
		char buffer[20];
		
		/* 打开文件用于读写 */
		fp = fopen("/home/li/file.txt", "w+");
		
		/* 写入数据到文件 */
		fwrite(c, strlen(c), 1, fp);
		
		/* 查找文件的开头 */
		fseek(fp, 0, SEEK_SET);
		
		/* 读取并显示数据 */
		fread(buffer, strlen(c), 1, fp);
		printf("%s\n", buffer);
		fclose(fp);
	}

    return 0;
}

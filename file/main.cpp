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
#include <bitset>
#include "../StringHelper.h"

int main(int argc, char *argv[])
{
    std::cout << "Start clean log!" << std::endl;

	std::string path = "/home/li/path.txt";
    std::ofstream outfile(path,std::ofstream::binary);
	for (size_t i = 0; i < 10; i++)
	{
		// float x = i * 1.1;
		// float y = i* 1.1;
		// std::cout << "save pose x:" << x << " y:" << y << std::endl;
		// outfile << x << "," << y << ";" << std::endl;
        outfile << 3.14;
	}

    outfile.close();


    int value = 0;
    std::ofstream outFile("/home/li/abin", std::ios::binary);
 
    if (outFile) {
        // 将float转换为char数组，然后写入文件
        std::cout << "out: " << reinterpret_cast<const char*>(&value) << std::endl;
        
        outFile.write(reinterpret_cast<const char*>(&value), sizeof(value));

        // 如果需要将二进制输出到文本文件以便阅读，可以使用以下代码
        // 注意这种方式可能不适用于非常大的数字或非常精确的浮点数
        // std::bitset<32> binaryValue(reinterpret_cast<unsigned long&>(value));
        // outFile << binaryValue.to_string();
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    std::ifstream is("/home/li/abin", std::ios::binary);
    if(is)
    {
  
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char * buffer = new char [length];

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read (buffer,length);

        if (is)
        {
            int v = 0;
            
            for (size_t i = 0; i < length; i++)
            {
                std::cout << i << " " << (uint16_t)buffer[i];
            }
            v = atoi(buffer);
            memcpy(&v,buffer,sizeof(int));
            std::cout << "all characters read successfully." << v;
        }
        else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();

        // ...buffer contains the entire file...

        delete[] buffer;
    }

	// std::ifstream ifs(path);
    // if (ifs.is_open())
    // {
    //     std::string line;
    //     while (std::getline(ifs, line))
    //     {
    //         std::cout << line << std::endl;
    //         std::vector<std::string> data = swr::util::StringHelper::Split2(line,',');
    //         if(data.size()>=2)
    //         {
    //             float x = atof(data[0].c_str());
    //             float y = atof(data[1].c_str());
	// 			std::cout << "read pose x:" << x << " y:" << y << std::endl;
    //         }
    //     }
    //     ifs.close();
    // }

    return 0;
}

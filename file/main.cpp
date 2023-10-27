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
#include "../StringHelper.h"

int main(int argc, char *argv[])
{
    std::cout << "Start clean log!" << std::endl;

	std::string path = "/home/li/path.txt";
    std::ofstream outfile(path,std::ofstream::binary);
	for (size_t i = 0; i < 10; i++)
	{
		float x = i * 1.1;
		float y = i* 1.1;
		std::cout << "save pose x:" << x << " y:" << y << std::endl;
		outfile << x << "," << y << ";" << std::endl;
	}

    outfile.close();

	std::ifstream ifs(path);
    if (ifs.is_open())
    {
        std::string line;
        while (std::getline(ifs, line))
        {
            std::cout << line << std::endl;
            std::vector<std::string> data = swr::util::StringHelper::Split2(line,',');
            if(data.size()>=2)
            {
                float x = atof(data[0].c_str());
                float y = atof(data[1].c_str());
				std::cout << "read pose x:" << x << " y:" << y << std::endl;
            }
        }
        ifs.close();
    }

    return 0;
}

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
	
    return 0;
}

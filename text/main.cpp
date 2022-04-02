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
#include "textFile.h"
#include "../FilePath.h"


int main(int argc, char *argv[])
{
    std::cout << "Start text demo!" << std::endl;
    textFile tf;
    tf.ReadText2();
    // tf.WriteText();
    // tf.ReadText();
    return 0;
}


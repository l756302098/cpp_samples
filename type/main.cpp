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
#include <list>
#include <memory>

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int*)malloc(5 * sizeof(int));

    // 错误：数组越界访问
    for (int i = 0; i <= 4; i++) {
        arr[i] = i;
    }

    printf("Array write complete!\n");

    free(arr);
    return 0;
}

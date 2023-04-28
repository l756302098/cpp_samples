#include <iostream>
#include "Data.h"

struct Data
{
    std::string name;
    std::string path;
    int age;
    swr::base_types::Data<bool> enableVirtualWall;
};


int main(){
    
    const Data data1{"li","/root"};
    std::cout << "name:" << data1.age << " path:" << data1.path 
    << " age:" << data1.age
    << std::endl;

    Data *tempData = (Data*)&data1;
    (*tempData).enableVirtualWall = false;

    Data data2 = data1;
    std::cout << "name:" << data2.age 
    << " path:" << data2.path 
    << " age:" << data2.age
    << std::endl;

    return 0;
}
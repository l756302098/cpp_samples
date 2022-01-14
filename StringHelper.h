#pragma once

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <vector>

namespace swr {
namespace util {

class StringHelper {
public:
    /*
    函数说明：对字符串中所有指定的子串进行替换
    参数：
    string resource_str            //源字符串
    string sub_str                //被替换子串
    string new_str                //替换子串
    返回值: string
    */
    static std::string subreplace(const std::string& resource_str,const std::string& sub_str,const std::string& new_str)
    {
        std::string dst_str = resource_str;
        std::string::size_type pos = 0;
        while((pos = dst_str.find(sub_str)) != std::string::npos)
        {
            std::cout << "replace " << pos << " " << sub_str.length() << std::endl;
            dst_str.replace(pos, sub_str.length(), new_str);
        }
        return dst_str;
    }
};

}  // namespace util
}  // namespace swr

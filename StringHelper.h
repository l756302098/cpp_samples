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

    // Split string.
    // e.g.  data = "a/b/c"  delim = '/'  >  "a" "b" "c"
    static inline std::vector<std::string> Split(const std::string& data,
                                                 char delim) {
        std::vector<std::string> vecString;

        std::size_t pos1 = 0;
        std::size_t pos2 = data.find(delim);

        while (std::string::npos != pos2) {
            if (0 != (pos2 - pos1)) {
                vecString.push_back(data.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
            pos2 = data.find(delim, pos1);
        }

        std::string&& sub = data.substr(pos1);
        if (!sub.empty()) {
            vecString.push_back(sub);
        }

        return vecString;
    }

    static inline std::vector<std::string> Split2(const std::string& data,
                                                 char delim) {
        std::vector<std::string> vecString;

        std::string::size_type pos1, pos2;
        pos2 = data.find(delim);
        pos1 = 0;
        while(std::string::npos != pos2)
        {
            vecString.push_back(data.substr(pos1, pos2-pos1));

            pos1 = pos2 + 1;
            pos2 = data.find(delim, pos1);
        }

        if(pos1 != data.length())
        {
            vecString.push_back(data.substr(pos1));
        }
        return vecString;
    }
};

}  // namespace util
}  // namespace swr

#pragma once

#include <vector>
#include <iostream>

#define MIN_AVAILABLE_SIZE (300 * 1024 * 1024)
namespace abby {
class StringUtil
{
    public:
    static std::vector<std::string> Split(const std::string& data,
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
}

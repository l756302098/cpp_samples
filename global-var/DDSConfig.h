#ifndef STATIC_VAR_H
#define STATIC_VAR_H
#include <string>

namespace wk {
    const static std::string PREFIX = "rt";
    const static std::string REQ_SUFFIX = "/request";
    const static std::string RESP_SUFFIX = "/response";

    extern std::string DDS_WIFI_NAME;
    extern std::string DDS_WIFI_PWD;
    extern int ROS_DOMAIN_ID;
}

#endif
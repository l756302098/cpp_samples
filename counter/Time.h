#pragma once

#include <sys/time.h>

namespace swr {

namespace util {

inline std::uint64_t Now() {
    struct timeval tvt;
    gettimeofday(&tvt, 0);
    return static_cast<std::uint64_t>(tvt.tv_sec);
}

inline std::string Date()
{
    struct tm stime;
    time_t now = time(0);
    localtime_r(&now, &stime);
    char buffer[256] = {0};
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &stime);
    std::string date(buffer);
    return date;
}

}  // namespace util
}  // namespace swr

#pragma once

#include <sys/time.h>

namespace swr {

namespace util {

inline std::uint64_t Now() {
    struct timeval tvt;
    gettimeofday(&tvt, 0);
    return static_cast<std::uint64_t>(tvt.tv_sec * 1000000 + tvt.tv_usec);
}

}  // namespace util
}  // namespace swr

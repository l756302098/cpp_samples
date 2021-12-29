#ifndef __COMMON_UTIL_HZ_COUNTER_
#define __COMMON_UTIL_HZ_COUNTER_

#include <sys/time.h>
#include <cstdint>
#include <atomic>

namespace swr {

namespace util {

struct Duration {
    std::int64_t sec;   // sencords
    std::int64_t usec;  // microseconds

    inline std::int64_t toMilliseconds() {
        return sec * 1000 + usec / 1000;
    }

    inline std::int64_t toMicroseconds() {
        return sec * 1000000 + usec;
    }
};

class HzCounter {
    std::uint64_t counter;
    std::atomic<double> hz;
    struct timeval tvStart, tvEnd;

    static const std::uint64_t RESET = 100000u;

public:
    HzCounter() : counter(0u),hz(0) {
        gettimeofday(&tvEnd, nullptr);
    };

    double Tick() {
        //double hz = 0.0;

        ++counter;
        if (counter > 1) {
            gettimeofday(&tvEnd, nullptr);
            hz = (counter - 1) /
                 ((tvEnd.tv_sec - tvStart.tv_sec) * 1000.0 +
                  (tvEnd.tv_usec - tvStart.tv_usec) / 1000.0) *
                 1000.0;
            if (counter > RESET) {
                counter -= RESET / 2u;
                auto t = RESET / 2u / hz;
                auto s = static_cast<std::uint64_t>(t);
                auto us = (t - s) * 1000000.0;
                tvStart.tv_sec += s;
                tvStart.tv_usec += us;
            }
        } else {
            gettimeofday(&tvStart, nullptr);
        }

        return hz;
    }

    void Reset() {
        counter = 0;
        hz = 0;
    }

    double GetHz() {
        if (counter == 0) {
            return 0;
        }
        return hz;
        /*
        struct timeval now;
        gettimeofday(&now, nullptr);
        return (counter - 1) /
               ((now.tv_sec - tvStart.tv_sec) * 1000.0 +
                (now.tv_usec - tvStart.tv_usec) / 1000.0) *
               1000.0;
        */
    }

    Duration SinceLastTick() {
        struct timeval now;
        gettimeofday(&now, nullptr);

        Duration d;
        d.sec = now.tv_sec - tvEnd.tv_sec;
        d.usec = now.tv_usec - tvEnd.tv_usec;

        return d;
    }
};

}  // namespace util
}  // namespace swr

#endif

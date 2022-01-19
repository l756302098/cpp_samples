#ifndef __COMMON_UTIL_HZ_COUNTER2_
#define __COMMON_UTIL_HZ_COUNTER2_

#include <sys/time.h>
#include <cstdint>
#include <deque>
#include <mutex>
#include "HzCounter.h"
#include "Time.h"
namespace swr {

namespace util {

class HzCounter2 {

    std::deque<std::uint64_t> msgTimeQueue;
    std::mutex lockMutex;
    std::atomic_int64_t lastPrintTime;
    static const std::uint8_t maxTime = 2u; // s

public:
    HzCounter2(){
        lastPrintTime = util::Now();
    };
    ~HzCounter2(){
        std::lock_guard<std::mutex> guard(lockMutex);
        msgTimeQueue.clear();
    };

    void Tick() {
        std::uint64_t now = util::Now();
        lastPrintTime = now;
        std::lock_guard<std::mutex> guard(lockMutex);
        msgTimeQueue.push_back(now);
        //std::cout << "add " << now << std::endl;
        if(msgTimeQueue.size() > 0)
        {
            bool isGt = now - msgTimeQueue.front() > maxTime * 1000000 ? true : false;
            while (isGt)
            {
                auto& first = msgTimeQueue.front();
                msgTimeQueue.pop_front();
                //std::cout << "del " << first << " now:" << now << std::endl;
                if(msgTimeQueue.size() > 0)
                {
                    isGt = now - msgTimeQueue.front() > maxTime * 1000000 ? true : false;
                }
                else{
                    isGt = false;
                }  
            }
        }
    }

    double GetHz() {
        double hz = 0;
        std::lock_guard<std::mutex> guard(lockMutex);
        std::uint64_t now = util::Now();
        if(msgTimeQueue.size() > 0)
        {
            bool isGt = now - msgTimeQueue.front() > maxTime * 1000000 ? true : false;
            while (isGt)
            {
                msgTimeQueue.pop_front();
                if(msgTimeQueue.size() > 0)
                {
                    isGt = now - msgTimeQueue.front() > maxTime * 1000000 ? true : false;
                }
                else{
                    isGt = false;
                }  
            }
        }
        if(msgTimeQueue.size() < 2)
        {
            return hz;
        }
        auto& first = msgTimeQueue.front();
        auto& last = msgTimeQueue.back();
        //calc mean
        std::int64_t diff = last - first;
        //std::int64_t diff = now - first;
        double mean = diff / (msgTimeQueue.size() - 1) / 1000000.0;
        hz = 1.0 / mean;
        return hz;
    }

    Duration SinceLastTick() {
        std::uint64_t now = util::Now();
        std::lock_guard<std::mutex> guard(lockMutex);
        std::uint64_t last = lastPrintTime;
        std::cout << "now:" << now << std::endl;
        // if(msgTimeQueue.size() > 0)
        // {
        //     last = msgTimeQueue.back();
        //     std::cout << "last:" << last << std::endl;
        // }
        Duration d;
        d.sec = (now - last) / 1000000;
        d.usec = now - last - d.sec * 1000000;
        std::cout << "sec:" << d.sec << std::endl;
        std::cout << "usec:" << d.usec << std::endl;
        return d;
    }
};

}  // namespace util
}  // namespace swr

#endif

#ifndef __RATE_H_
#define __RATE_H_

#include <sys/time.h>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace swr {

namespace util {

class Rate
{
    std::uint64_t base_time;
    std::uint64_t counter;
    struct timeval tvStart, tvEnd;

    std::mutex mtxCv;
    std::condition_variable cv;
public:
    enum {
        SLEEP_RTC_OK,
        SLEEP_RTC_NOT_SLEEP,
        SLEEP_RTC_INTERRUPTED,
    };
    Rate(double hz) : counter(0)
    {
        std::cout << "hz:" << hz << std::endl;
        base_time = 1000000000 / hz;
        std::cout << "base_time:" << base_time << std::endl;
    }

    void interrupt()
    {
        counter = 0;
        // wakeup
        cv.notify_one();
    }

    int sleep()
    {
        int rlt;
        
        if (counter > 0)
        {
            gettimeofday(&tvEnd, NULL);
            std::uint64_t time_left =  base_time * (counter + 1) - ((tvEnd.tv_sec - tvStart.tv_sec) * 1000000 + (tvEnd.tv_usec - tvStart.tv_usec)) * 1000;
            if (time_left > 0)
            {
                // std::this_thread::sleep_for(std::chrono::nanoseconds(time_left));
                std::unique_lock <std::mutex> lck(mtxCv);
                auto flag = cv.wait_for(lck, std::chrono::nanoseconds(time_left));
                rlt = ((flag == std::cv_status::timeout) ? SLEEP_RTC_OK : SLEEP_RTC_INTERRUPTED);
            }
            else
            {
                std::this_thread::yield();
                rlt = SLEEP_RTC_NOT_SLEEP;
            }

            if (counter > 10000000u && time_left > 0)
            {
                auto at = base_time * counter;
                auto ts = at / 1000000000;
                auto tus = (at - ts * 1000000000) / 1000;
                tvStart.tv_sec += ts;
                tvStart.tv_usec += tus;
                counter = 1;
            }
            else
            {
                ++counter;
            }
        }
        else
        {
            gettimeofday(&tvStart, NULL);
            // std::this_thread::sleep_for(std::chrono::nanoseconds(base_time));
            std::unique_lock <std::mutex> lck(mtxCv);
            auto flag = cv.wait_for(lck, std::chrono::nanoseconds(base_time));
            rlt = ((flag == std::cv_status::timeout) ? SLEEP_RTC_OK : SLEEP_RTC_INTERRUPTED);
            ++counter;
        }
        
        
        return rlt;
    }

};

}
}



#endif

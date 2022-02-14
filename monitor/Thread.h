#pragma once

#include <unistd.h>
#include <sys/syscall.h>
#include <functional>
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include "Rate.h"

namespace swr {

namespace util {


class Thread
{

public:
    class Sleeper
    {
        std::mutex mtxCv;
        std::condition_variable cv;
    public:

        template<typename _Rep, typename _Period>
        bool Sleep(const std::chrono::duration<_Rep, _Period>& rtime)
        {
            std::cv_status flag;
            std::unique_lock <std::mutex> lck(mtxCv);
            flag = cv.wait_for(lck, rtime);

            return flag == std::cv_status::timeout;
        }

        void Interrupt()
        {
            cv.notify_one();
        }
    } ;

    Thread()
    {
        running = false;
        interrupted = false;
        th = nullptr;
    }

    virtual ~Thread()
    {
        if (th != nullptr)
        {
            if (th->joinable())
            {
                try {
                    th->join();
                }
                catch (std::exception& e)
                {
                    // do nothing
                }
            }

            delete th;
        }
    }

    static long int GetTid()
    {
        return syscall(SYS_gettid);
    }

    void Start()
    {
        if (!running && th == nullptr)
        {
            th = new std::thread(std::bind(&Thread::InnerRun, this));
        }
    }

    template<typename _Rep, typename _Period>
    inline bool Sleep(const std::chrono::duration<_Rep, _Period>& rtime)
    {
        return sleeper.Sleep(rtime);
    }

    inline void SetRate(double hz)
    {
        rate = std::make_shared<Rate>(hz);
    }

    inline bool RegularSleep()
    {
        if (!interrupted)
        {
            return rate->sleep() != Rate::SLEEP_RTC_INTERRUPTED;
        }
        return false;
    }

    inline bool Sleep()
    {
        return RegularSleep();
    }

    void Interrupt(bool blocked = true)
    {
        interrupted = true;

        sleeper.Interrupt();
        rate->interrupt();

        if (th != nullptr)
        {
            sleeper.Interrupt();

            if (blocked && th->joinable())
            {
                try {
                    th->join();
                } catch (...) {
                }
            }
            else
            {
                try {
                    th->detach();
                } catch (...) {
                }
            }

            delete th;
            th = nullptr;
        }
    }

    bool IsRunning()
    {
        return running;
    }

    bool IsInterrupted()
    {
        return interrupted;
    }

protected:
    virtual void Run() = 0;

private:
    Sleeper sleeper;
    std::thread *th;
    std::atomic_bool running;
    std::atomic_bool interrupted;
    std::shared_ptr<Rate> rate;

    void InnerRun()
    {
        running = true;
        Run();
        running = false;
    }
};

}}

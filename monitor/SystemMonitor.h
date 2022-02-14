#ifndef __SYSTEM_MOMITOR_
#define __SYSTEM_MOMITOR_

#include "Thread.h"
#include <iostream>

class SystemMonitor: public swr::util::Thread
{
private:
    /* data */
    double cpuUsedPecent = 0.0;
    std::uint32_t memUsedBytes = 0;
    bool enableWatching = false;
    bool enableReport = false;
    bool enableEcho = false;
    double rate = 1.0;

    void Run() override;
public:
    SystemMonitor(/* args */);
    ~SystemMonitor();
    void Init();
};

#endif


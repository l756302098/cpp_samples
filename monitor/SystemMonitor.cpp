#include "SystemMonitor.h"
#include "SysOper.h"

SystemMonitor::SystemMonitor(/* args */)
{
}

SystemMonitor::~SystemMonitor()
{
}

static unsigned long getTotalCPUTime(swr::util::SysOper::TotalCPUOccupy* t) {
    FILE* fd = fopen("/proc/stat", "r");
    if (nullptr == fd) {
        printf("fopen /proc/stat failure.\n");
        return 0;
    }

    char buff[512] = {0};
    char* retfgets = fgets(buff, sizeof(buff), fd);
    (void)retfgets;

    char name[64] = {0};
    sscanf(buff, "%s %ld %ld %ld %ld %ld %ld %ld", name, &t->user, &t->nice,
           &t->sys, &t->idle, &t->iowait, &t->irq, &t->sirq);
    fclose(fd);

    return t->user + t->nice + t->sys + t->idle + t->iowait + t->irq +
           t->sirq;
}

static void Update(int pid, swr::util::SysOper::TotalCPUOccupy &t, unsigned long &tco, unsigned long &pc)
{
    getTotalCPUTime(&t);
    tco =
        t.user + t.nice + t.sys + t.idle + t.iowait + t.irq + t.sirq;
    pc = swr::util::SysOper::getProcCPUTime(pid);
}

void SystemMonitor::Run()
{
    auto pid = getpid();
    swr::util::SysOper::TotalCPUOccupy lastT;
    unsigned long lastTco;
    unsigned long lastPc;
    Update(pid, lastT, lastTco, lastPc);

    while (!IsInterrupted())
    {
        if (Thread::RegularSleep())
        {
            swr::util::SysOper::TotalCPUOccupy curT;
            unsigned long curTco;
            unsigned long curPc;
            Update(pid, curT, curTco, curPc);

            float cpuOccupy = 0.0;
            if (0 != curTco - lastTco) {
                cpuOccupy = 100.0 * (curPc - lastPc) / float(curTco - lastTco);
            }
            cpuOccupy *= get_nprocs();

            cpuUsedPecent = cpuOccupy;
            memUsedBytes = swr::util::SysOper::getProcMem(pid);

            lastT = curT;
            lastTco = curTco;
            lastPc = curPc;

            if (enableEcho)
            {
                std::cout << "------------------------Resource-------------------------" << std::endl;
                std::cout << "CPU occupied: " << cpuUsedPecent << "%" << std::endl;
                std::cout << "RAM occupied: " << memUsedBytes << "KB" << std::endl;
                std::cout << "---------------------------------------------------------" << std::endl;
            }
        }
    }
}

void SystemMonitor::Init()
{
    enableEcho = true;
    Thread::SetRate(1);
    Thread::Start();
}
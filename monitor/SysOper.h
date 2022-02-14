#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string>

namespace swr {
namespace util {

class SysOper {
public:
    static const unsigned short VMRSS_LINE = 22;
    static const unsigned short VMSIZE_LINE = 18;
    static const unsigned short PROCESS_ITEM = 14;

    typedef struct {
        unsigned long user;
        unsigned long nice;
        unsigned long sys;
        unsigned long idle;
        unsigned long iowait;
        unsigned long irq;
        unsigned long sirq;
    } TotalCPUOccupy;

    typedef struct {
        unsigned int pid;
        unsigned long utime;
        unsigned long stime;
        unsigned long cutime;
        unsigned long cstime;
    } ProcCPUOccupy;

public:
    // get total cpu occupy
    // [note] blocking threads
    static inline float getTotalCPUOccupy(unsigned int milliseconds = 1000) {
        TotalCPUOccupy t1;
        unsigned long tco1 = getTotalCPUTime(&t1);

        usleep(milliseconds * 1000);

        TotalCPUOccupy t2;
        unsigned long tco2 = getTotalCPUTime(&t2);

        long sum = tco2 - tco1;
        double used = t2.user + t2.nice + t2.sys - t1.user - t1.nice - t1.sys;
        return (0 != sum) ? used / sum : 0;
    }

    // get process cpu time
    static inline unsigned long getProcCPUTime(unsigned int pid) {
        char fileName[64] = {0};
        sprintf(fileName, "/proc/%d/stat", pid);

        FILE* fd = fopen(fileName, "r");
        if (nullptr == fd) {
            printf("fopen %s failure.\n", fileName);
            return 0;
        }

        char buf[512] = {0};
        char* fgetret = fgets(buf, sizeof(buf), fd);
        (void)fgetret;

        ProcCPUOccupy t;
        sscanf(buf, "%u", &t.pid);
        const char* q = getNItems(buf, SysOper::PROCESS_ITEM);
        sscanf(q, "%ld %ld %ld %ld", &t.utime, &t.stime, &t.cutime, &t.cstime);
        fclose(fd);

        return (t.utime + t.stime + t.cutime + t.cstime);
    }

    // get process cpu  occupy
    // [note] blocking threads
    static inline float getProcCPUOccupy(unsigned int pid,
                                         unsigned int milliseconds = 1000) {
        TotalCPUOccupy t1;
        getTotalCPUTime(&t1);
        unsigned long tco1 =
            t1.user + t1.nice + t1.sys + t1.idle + t1.iowait + t1.irq + t1.sirq;
        unsigned long pc_1 = getProcCPUTime(pid);

        usleep(milliseconds * 1000);

        TotalCPUOccupy t2;
        getTotalCPUTime(&t2);
        unsigned long tco2 =
            t2.user + t2.nice + t2.sys + t2.idle + t2.iowait + t2.irq + t2.sirq;
        unsigned long pc_2 = getProcCPUTime(pid);

        float cpuOccupy = 0.0;
        if (0 != tco2 - tco1) {
            cpuOccupy = 100.0 * (pc_2 - pc_1) / float(tco2 - tco1);
        }
        cpuOccupy *= get_nprocs();

        return cpuOccupy;
    }

    // get process occupy memory. return KB
    static inline unsigned int getProcMem(unsigned int pid) {
        char fileName[64] = {0};
        sprintf(fileName, "/proc/%d/status", pid);

        FILE* fd = fopen(fileName, "r");
        if (nullptr == fd) {
            printf("fopen %s failure.\n", fileName);
            return 0;
        }

        char lineBuff[512] = {0};
        for (int i = 0; i < SysOper::VMRSS_LINE - 1; i++) {
            char* fgetret = fgets(lineBuff, sizeof(lineBuff), fd);
            (void)fgetret;
        }
        char* fgetret = fgets(lineBuff, sizeof(lineBuff), fd);
        (void)fgetret;
        fclose(fd);

        int vmrss;
        char name[64];
        sscanf(lineBuff, "%s %d", name, &vmrss);

        return vmrss;
    }

    // get process virtual memory. return KB
    static inline unsigned int getProcVirtualMem(unsigned int pid) {
        char fileName[64] = {0};
        sprintf(fileName, "/proc/%d/status", pid);

        FILE* fd = fopen(fileName, "r");
        if (nullptr == fd) {
            printf("fopen %s failure.\n", fileName);
            return 0;
        }

        char buf[512] = {0};
        for (int i = 0; i < SysOper::VMSIZE_LINE - 1; i++) {
            char* fgetret = fgets(buf, sizeof(buf), fd);
            (void)fgetret;
        }
        char* fgetret = fgets(buf, sizeof(buf), fd);
        (void)fgetret;
        fclose(fd);

        int vmsize;
        char name[64] = {0};
        sscanf(buf, "%s %d", name, &vmsize);

        return vmsize;
    }

    // get host name
    static inline std::string GetHostName() {
        struct utsname buf;
        if (0 != uname(&buf)) {
            return std::move("");
        }
        return std::move(buf.nodename);
    }

    // get user name
    static inline std::string GetUserName() {
        return std::move(getenv("USER"));
    }

private:
    // get total cpu time
    static inline unsigned long getTotalCPUTime(TotalCPUOccupy* t) {
        FILE* fd = fopen("/proc/stat", "r");
        if (nullptr == fd) {
            printf("fopen /proc/stat failure.\n");
            return 0;
        }

        char buff[512] = {0};
        char* fgetret = fgets(buff, sizeof(buff), fd);
        (void)fgetret;

        char name[64] = {0};
        sscanf(buff, "%s %ld %ld %ld %ld %ld %ld %ld", name, &t->user, &t->nice,
               &t->sys, &t->idle, &t->iowait, &t->irq, &t->sirq);
        fclose(fd);

        return t->user + t->nice + t->sys + t->idle + t->iowait + t->irq +
               t->sirq;
    }

    static const char* getNItems(const char* buffer, int N) {
        const char* ptr = buffer;
        int counter = 0;
        while (nullptr != ptr && '\0' != *ptr) {
            if (' ' == *ptr) {
                counter++;
                if (counter == N - 1) {
                    ptr++;
                    break;
                }
            }
            ptr++;
        }
        return ptr;
    }
};

}  // namespace util
}  // namespace swr

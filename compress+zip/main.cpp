/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

#include "../StringHelper.h"

const std::string appName = "i18R";

int system_ex(const char *cmdstring, unsigned int timeout)   /* with appropriate signal handling */
{
    pid_t               pid;
    int                 status;
    struct sigaction    ignore, saveintr, savequit;
    sigset_t            chldmask, savemask;
 
    //精度换成十分之一秒
    timeout *= 10;
    if (timeout == 0)
        timeout = 0xFFFFFFFF;
 
    if (cmdstring == NULL)
        return(1);      /* always a command processor with UNIX */
 
    ignore.sa_handler = SIG_IGN;    /* ignore SIGINT and SIGQUIT */
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if (sigaction(SIGINT, &ignore, &saveintr) < 0)
        return(-1);
    if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
        return(-1);
    sigemptyset(&chldmask);         /* now block SIGCHLD */
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
        return(-1);
 
    if ((pid = fork()) < 0) {
        return -1;    /* probably out of processes */
    } else if (pid == 0) {          /* child */
        /* restore previous signal actions & reset signal mask */
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);
/*通常exec会放在fork() 函数的子进程部分, 来替代子进程执行啦, 执行成功后子程序就会消失,  但是执行失败的话, 必须用exit()函数来让子进程退出!*/
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);/*<strong>exec函数会取代执行它的进程,  也就是说, 一旦exec函数执行成功, 它就不会返回了, 进程结束.   但是如果exec函数执行失败, 它会返回失败的信息,  而且进程继续执行后面的代码!</strong>*/
        _exit(127);     /* exec error */
    }
 
    /* parent */
    int ret = 0;
    while (timeout-- > 0 &&
        (ret = waitpid(pid, &status, WNOHANG)) == 0)
        usleep(100*1000);
 
    /* restore previous signal actions & reset signal mask */
    if (sigaction(SIGINT, &saveintr, NULL) < 0)
        return(-1);
    if (sigaction(SIGQUIT, &savequit, NULL) < 0)
        return(-1);
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
        return(-1);
 
    if (ret < 0)
        return -1;
 
    if (ret > 0)
        return status;
 
    kill(pid, SIGKILL);
    waitpid(pid, &status, 0);
    return -2;
}

int get_cmd_results(const char *cmdstring, char *buff, int size)
{
    char cmd_string[256] = {0};
    char tmpfile[256] = {0};
    char tmp_buf[256] = {0};
    int fd;
    int tmp_fd;
    int nbytes;
 
    memset(buff, 0, size);


    // printf("{sizeof(cmdstring):%d}\n",sizeof(cmdstring));
    // printf("{strlen(cmdstring):%d}\n",strlen(cmdstring));
    // printf("{sizeof(tmpfile):%d}\n",sizeof(tmpfile));
    // printf("{strlen(tmpfile):%d}\n",strlen(tmpfile));
    if((cmdstring == NULL) ||
        (strlen(cmdstring) > (sizeof(tmpfile) + 8)) ||
        ((strlen(cmdstring) + strlen(tmpfile) + 5) > sizeof(cmd_string)))
    {
        printf("cmd is too long or NULL!\n");
        return -1;
    }
    sscanf(cmdstring, "%[a-Z]", tmp_buf);/*%[a-z] 表示匹配a到z中任意字符，贪婪性(尽可能多的匹配) */
    sprintf(tmpfile, "/tmp/%s-XXXXXX", tmp_buf);
 
    tmp_fd = mkstemp(tmpfile);
    if(tmp_fd < 0)
    {
        printf("mkstemp failed\n");
        return -1;
    }
    close(tmp_fd);
 
    sprintf(cmd_string, "%s > %s 2>&1", cmdstring, tmpfile);/*标准输出（1），标准错误（2）都输出到临时文件*/
    if(system_ex(cmd_string, 20) < 0)
    {
        printf("run \"%s\" ret < 0!\n", cmd_string);
    }
 
    fd = open(tmpfile, O_RDONLY);
    if(fd < 0)
    {
        printf("open %s failed!\n", tmpfile);
        nbytes = -1;
    }
    else
    {
        nbytes = read(fd, buff, size - 1);
        close(fd);
    }
 
    memset(cmd_string, 0, sizeof(cmd_string));
    sprintf(cmd_string, "rm -rf /tmp/%s-*", tmp_buf);
    system_ex(cmd_string, 20);
 
    return nbytes;
}

bool get_cmd(const std::string& cmdStr,std::string& resultStr){
    char resultBuf[128];
    std::cout << "cmd:" << cmdStr << std::endl;
    int r = get_cmd_results(cmdStr.c_str(),resultBuf,128);
    std::cout << "result:" << r << " buffer:" << resultBuf << std::endl;
    
    std::string result = std::string(resultBuf);
    std::vector<std::string> rv = swr::util::StringHelper::Split(result,' ');
    for (auto& item: rv)
    {
        std::cout << "item:" << item << std::endl;
    }
    if(rv.size() < 1)
    {
        return false;
    }
    resultStr = rv.at(0);
    return true;
}

int main(int argc, char *argv[])
{
    std::cout << "Start compress+zip demo!" << std::endl;
    std::string folderName = "40016023160319_ncu_202107101302_202107131402_icelog.l";
    
    std::string cmd = "echo -n i18R | sha256sum";
    std::string data1;
    if(!get_cmd(cmd,data1))
    {
        return false;
    }

    cmd = "echo -n "+ folderName + data1 +" | sha256sum";
    std::string data2;
    if(!get_cmd(cmd,data2))
    {
        return false;
    }

    cmd = "echo -n "+ data2 +" | base64";
    std::string data3;
    if(!get_cmd(cmd,data3))
    {
        return false;
    }

    std::cout << "data1:" << data1 << " data2:" << data2
        << " data3:" << data3 << std::endl;

    std::string pwd = data3.substr(0,32);
    std::cout << "pwd:" << pwd << std::endl;
    
    return 0;
}


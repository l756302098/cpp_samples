/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../StringHelper.h"

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
    char cmd_string[200] = {0};
    char tmpfile[100] = {0};
    char tmp_buf[100] = {0};
    int fd;
    int tmp_fd;
    int nbytes;
 
    memset(buff, 0, size);
 
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

int main(int argc, char *argv[])
{
    std::string filePath = "/home/li/app/INDEMINDAPP_ICE_EVT3.2_4.deb";
    std::string cmd = "md5sum " + filePath;
    std::cout << "cmd:" << cmd << std::endl;
    char resultBuf[80];
    auto result = get_cmd_results(cmd.c_str(),resultBuf,80);
    if (result != 0)
    {
        std::cout << "md5sum faile." << std::endl;
    }
    printf("result: %s \n",resultBuf); 
    std::string resultStr(&resultBuf[0],&resultBuf[strlen(resultBuf)]);
    std::vector<std::string> spVector = swr::util::StringHelper::Split(resultStr,' ');
    for(int i = 0; i <= spVector.size();i++)
    {
        std::cout << i << " " << spVector[i] << std::endl;
    }
    //sha256
    memset(resultBuf,0,sizeof(resultBuf));
    cmd = "sha256sum " + filePath;
    result = system(cmd.c_str());
    std::cout << "cmd:" << cmd << std::endl;
    if (result != 0)
    {
        std::cout << "sha256sum failed." << std::endl;
    }
    printf("result: %s \n",resultBuf);
    return 0;
}


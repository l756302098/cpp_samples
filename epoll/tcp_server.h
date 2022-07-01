#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<sys/types.h>
#include <atomic>

namespace abby {
class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    void Listen();
    void Stop();
private:
    std::atomic<bool> running;
private:
    //函数声明
    int socket_bind(const char* ip, int port);
    void do_epoll(int listenfd);
    void handle_events(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf);
    void handle_accept(int epollfd, int listenfd);
    void do_read(int epollfd, int fd, char* buf);
    void do_write(int epollfd, int fd, char* buf);
    void add_event(int epollfd, int fd, int state);
    void modify_event(int epollfd, int fd, int state);
    void delete_event(int epollfd, int fd, int state);
};
}

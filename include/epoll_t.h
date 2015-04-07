#ifndef EPOLL_H_
#define EPOLL_H_

#include<sys/epoll.h>
#include<iostream>
#include<map>
#include<string>
#include"thread_pool.h"
#include"mutex.h"
#include"execute.h"
#include"sysutil.h"
#include"text.h"

using std::cout;
using std::endl;
using std::map;
using std::string;
typedef void (*callback_t) (const char *, size_t cnt, int fd);

typedef struct {
    int epoll_fd_;
    int listenfd_;
    struct epoll_event events_[2048];
    int nready_; //准备好的数目
    callback_t callback_; //回调函数
} epoll_t;


void epoll_init(epoll_t *et, int listenfd, callback_t callback);
void epoll_loop(epoll_t *et);
void epoll_handle_fd(epoll_t *et, THREADPOOL::CThread_pool& pool, EXECUTE::CRun& arun, Text& text);
void epoll_destroy(epoll_t *et);



#endif //EPOLL_H_

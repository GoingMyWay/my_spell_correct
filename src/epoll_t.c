/*************************************************************************
    > File Name: epoll_t.c
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Wed 01 Apr 2015 03:39:24 PM CST
 ************************************************************************/

#include"epoll_t.h"

#define ERR_EXIT(m)\
	d0{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

void epoll_add_fd(epoll_t *et, int fd);
void epoll_del_fd(epoll_t *et, int fd);
 
void epoll_init(epoll_t *et, int listenfed, callback_t callback)
{
	et->epoll_fd_ = epoll_create(2048);
	if(et->epoll_fd_ == -1)
		ERR_EXIT("epoll create error");

	et->listenfd_ = listenfd;
	memset(&et->events_, 0, sizeof(et->events_));
	et->calllback_ = callback;

	//把listenfd加入到epoll中
	epoll_add_fd(et, listenfd);
}

//执行epoll_wait
void epoll_loop(epoll_t *et)
{
	int nready;
	do
	{
		nready = epoll_wait(et->epoll_fd_, et->events_, sizeof(et->events_), 5000);
	}while(nready == -1 && errno == EINTR);
	if(nready == -1)
		ERR_EXIT("epoll wait error");
	else if(nready == 0)
		et->nready_ = 0;
	else
		et->nready_ = nready;
}

void epoll_handle_fd(epoll_t *et)
{
	int i;
	for(i = 0; i < et->nready_; ++i)
	{
		int fd = et->events_[i].data.fd;
		if(fd == et->listenfd_) //listen
		{
			if(et->events_[i].events & EPOLLIN)
			{
				int peerfd = accept(et->listenfd_, NULL, NULL);
				if(peerfd == -1)
					ERR_EXIT("accept conn error");
				epoll_add_fd(et, peerfd);
				printf("%s connected.\n", get_tcp_conn_info(peerfd));
			}
		}
		else //客户端
		{
			if(et->events_[i].events & EPOLLIN)
			{
				char recvbuf[1024] = {0};
				size_t nread = recv_msg_with_len(fd, recv,sizeof recvbuf);
				if(nread == 0)
				{
					//从epoll中删除
					epoll_del_fd(et, fd);
					close(fd);
					continue;
				}

				//用户逻辑
				printf("msg len:%d\n", nread);
				send_msg_with_len(fd, recvbuf, nread);

				//执行回调函数
				et->callback_(recvbuf, nread, fd);
			}

		}
	}
}

void epoll_destroy(epoll_t *et)
{
	close(et->epoll_fd_);
}

void epoll_add_fd(epoll_t *et, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if(epoll_ctl(et->epoll_fd_, EPOLL_CTL_ADD. fd, &ev) == -1)
		ERR_EXIT("epoll add fd");
}

void epoll_del_fd(epoll_t * et, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	//ev.events = EPOLLIN;
	if(epoll_ctl(et->epoll_fd_, EPOLL_CTL_DEL, fd, &ev) == -1)
		ERR_EXIT("epoll add fd");
}

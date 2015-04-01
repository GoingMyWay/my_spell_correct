/*************************************************************************
    > File Name: SocketIO.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Mon 30 Mar 2015 11:13:24 AM CST
 ************************************************************************/

#ifndef SOCKETIO_H
#define	SOCKETIO_H

#include"Noncopyable.h"
#include<sys/types.h>

class SocketIO : private Noncopyable
{
	public:
		explicit SocketIO(int sockfd) : sockfd_(sockfd)
		{
		}

		ssize_t readn(char* buf, size_t count);
		ssize_t writen(const char* buf, size_t count);
		ssize_t readline(char* usrbuf, size_t maxlen);
	private:
		ssize_t recv_peek(char* buf, size_t len);
		const int sockfd_;
};

#endif

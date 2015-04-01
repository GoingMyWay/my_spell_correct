/*************************************************************************
    > File Name: Socket.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Mon 30 Mar 2015 10:03:59 AM CST
 ************************************************************************/

#ifndef SOCKET_H
#define SOCKET_H

#include"InetAddress.h"
#include"Noncopyable.h"

class Socket : private Noncopyable
{
	public:
		explicit Socket(int sockfd);
		Socket();
		~Socket();

		void init(int protocol);
		void bindAddress(const InetAddress &addr);
		void listen();
		int accept();
		int fd() const 
		{
			return sockfd_;
		}
		
		void shutdownWrite();
		
		void setTcpNoDelay(bool on);
		void setReuseAddr(bool on);
		void setReusePort(bool on);
		void setKeepAlive(bool on);

		static InetAddress getLocalAddress(int sockfd);
		static InetAddress getPeerAddress(int sockfd);

	private:
		int sockfd_;
};

#endif

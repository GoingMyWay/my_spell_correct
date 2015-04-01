/*************************************************************************
    > File Name: Socket.cpp
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Mon 30 Mar 2015 10:12:07 AM CST
 ************************************************************************/

#include"Socket.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/tcp.h>
#include<netdb.h>

Socket::Socket(int sockfd) : sockfd_(sockfd)
{
}

Socket::Socket()
{
}

Socket::~Socket()
{
	::close(sockfd_);
}

void Socket::init(int protocol)
{
	int socketfd;
	if(protocol == 0)
	{
		sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(-1 == sockfd_)
		{
			perror("create socket error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		sockfd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(-1 == sockfd_)
		{
			perror("create socket error");
			exit(EXIT_FAILURE);
		}
	}
}

void Socket::bindAddress(const InetAddress &addr)
{
	if(::bind(sockfd_, (SA*)addr.getSockAddrInet(), sizeof(addr)) == -1)
	{
		fprintf(stderr, "bind address error\n");
	}
}

void Socket::listen()
{
	if(::listen(sockfd_, SOMAXCONN) == -1)
	{
		fprintf(stderr, "listen address error\n");
		exit(EXIT_FAILURE);
	}
}

int Socket::accept()
{
	int fd = ::accept(sockfd_, NULL, NULL);
	if(fd == -1)
	{
		fprintf(stderr, "eccept error\n");
		exit(EXIT_FAILURE);
	}
	printf("accept ok\n");
	return fd;
}

void Socket::shutdownWrite()
{
	if(::shutdown(sockfd_, SHUT_WR) == -1)
	{
		fprintf(stderr, "shutdown error\n");
		exit(EXIT_FAILURE);
	}
}

void Socket::setTcpNoDelay(bool on)
{
	int optval = on ? 1 : 0;
	if(::setsockopt(sockfd_, 
					IPPROTO_TCP,
					TCP_NODELAY,
					&optval,
					static_cast<socklen_t>(sizeof(optval))) == -1)
	{
		fprintf(stderr, "setTcpNoDelay error\n");
		exit(EXIT_FAILURE);
	}
}

void Socket::setReuseAddr(bool on)
{
	int optval = on ? 1 : 0;
	if(::setsockopt(sockfd_,
					SOL_SOCKET,
					SO_REUSEADDR,
					&optval,
					static_cast<socklen_t>(sizeof(optval))) == -1)
	{
		fprintf(stderr, "setReuseAddr error\n");
		exit(EXIT_FAILURE);
	}
}

void Socket::setReusePort(bool on)
{
#ifdef SO_REUSEPORT
	int optval = on ? 1 : 0;
	int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
				&optval, static_cast<socklen_t>(sizeof(optval)));
	if(ret < 0)
	{
		fprintf(stderr, "setReusePort error\n");
		exit(EXIT_FAILURE);
	}
#else
	if(on)
	{
		fprintf(stderr, "SO_REUSEPORT is not supported.\n");
	}
#endif
}

void Socket::setKeepAlive(bool on)
{
	int optval = on ? 1 : 0;
	if(::setsockopt(sockfd_, 
					SOL_SOCKET,
					SO_KEEPALIVE,
					&optval,
					static_cast<socklen_t>(sizeof(optval))) == -1)
	{
		fprintf(stderr, "setKeepAlive error\n");
		exit(EXIT_FAILURE);
	}
}

InetAddress Socket::getLocalAddress(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	if(::getsockname(sockfd, (SA*)&addr, &len) == -1)
	{
		fprintf(stderr, "getLocalAddress\n");
		exit(EXIT_FAILURE);
	}
	return InetAddress(addr);
}

InetAddress Socket::getPeerAddress(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	if(::getpeername(sockfd, (SA*)&addr, &len) == -1)
	{
		fprintf(stderr, "getPeerAddres\n");
		exit(EXIT_FAILURE);
	}
	return InetAddress(addr);
}

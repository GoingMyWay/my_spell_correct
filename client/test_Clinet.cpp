/*************************************************************************
  > File Name: test_Clinet.cpp
  > Author: Alexander
  > Mail: scutqiuwei@163.com 
  > Created Time: Mon 30 Mar 2015 11:36:38 AM CST
 ************************************************************************/

#include"InetAddress.h"
#include"ClientSocket.h"
#include"SocketIO.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char** argv)
{
	InetAddress addr("127.0.0.1", 9981);
	ClientSocket cltSock;
	cltSock.init(IPPROTO_TCP);
	cltSock.connect(addr);
	SocketIO sio(cltSock.get_socket());

	char sendbuf[1024];
	char recvbuf[1024];

	while(printf("please inpute:"), memset(sendbuf, 0, sizeof(sendbuf)),gets(sendbuf)!=NULL)
	{
		int len = sio.writen(sendbuf, strlen(sendbuf));
		printf("send %d bytes\n", len);

		memset(recvbuf, 0, sizeof(recvbuf));
		::read(cltSock.get_socket(), recvbuf, sizeof(sendbuf));
		printf("recv from server: %s\n", recvbuf);
	}
	return 0;
}

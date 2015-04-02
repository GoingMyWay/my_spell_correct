/*************************************************************************
  > File Name: main.cpp
  > Author: Alexander
  > Mail: scutqiuwei@163.com 
  > Created Time: Sat 28 Mar 2015 10:15:57 AM CST
 ************************************************************************/

#include"mutex.h"
#include"execute.h"
#include"thread_pool.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<iostream>

#include"InetAddress.h"
#include"Socket.h"
#include"SocketIO.h"
#include"epoll_t.h"
#include<string.h>
#include<unistd.h>

#include"text.h"

void foo(const char* buf, size_t cnt, int peerfd)
{
	printf("receive msg:%d\n", cnt);
	//send_msg_with_len(peerfd, buf, cnt);
}


int main(int argc, char* argv[])
{
	//read text 
	Text text("/home/admin/cpp/my_spell_correct/data/test.txt");
	if(text.init())
		cout << "open file ok" << endl;
	map<string, int> words = text.get_map();
	//thread pool 
	THREADPOOL::CThread_pool pool;
	EXECUTE::CRun arun(&pool.m_que);
	pool.on(&arun);
	//epoll
	int listenfd = tcp_server("127.0.0.1", 9981);
	epoll_t et;
	epoll_init(&et, listenfd, &foo);

	while(1)
	{
		epoll_loop(&et);
		epoll_handle_fd(&et, pool, arun);
	}

	epoll_destroy(&et);
	
	close(listenfd);


#if 0
	//read text
	Text text("/home/admin/cpp/my_spell_correct/data/test.txt");
	if(text.init())
	{
		cout << "open file ok" << endl;
	}
	map<string, int> words = text.get_map();

	//socket
	InetAddress addr("127.0.0.1", 9981);
	Socket sock;
	sock.init(0);

	sock.setTcpNoDelay(false);
	sock.setReusePort(true);
	sock.setReuseAddr(true);
	sock.setKeepAlive(false);

	sock.bindAddress(addr);
	sock.listen();

	int peerfd = sock.accept();
	SocketIO sio(peerfd);
	char recvbuf[1024] ;

	//thread pool 
	THREADPOOL::CThread_pool pool;
	EXECUTE::CRun arun(&pool.m_que);
	pool.on(&arun);

	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		int len =  ::read(peerfd, recvbuf, sizeof(recvbuf));
		//printf("len is %d\n", len);
		if( len > 0)
		{
			printf("receive msg: %s\n", recvbuf);
		}
		else
		{
			std::cout << "a client exit" << std::endl;
			exit(1);
		}

		string val = recvbuf;
		EXECUTE::CThread_execute* ptr = new EXECUTE::CThread_execute(val);
		cout << "--send to client: " << ::write(peerfd, recvbuf, strlen(recvbuf)) 
			 << " bytes " << endl;
		pool.m_que.produce(ptr);
		arun.run();
		//ptr->execute();
	}
#endif
	return 0;
}

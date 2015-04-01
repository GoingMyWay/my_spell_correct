/*************************************************************************
    > File Name: thread.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Fri 27 Mar 2015 10:51:13 PM CST
 ************************************************************************/

#ifndef __THREAD_H
#define __THREAD_H
#include"queue.h"
#include<iostream>
#include<pthread.h>

namespace THREAD_POOL
{
	class CThread_pool;
}

namespace THREAD
{
	class CThread_RUN
	{
		public:
			virtual void run() = 0;
	};

	class CThread
	{
		public:
			CThread() {}
			CThread(void* arg) {}
			void start(CThread_RUN* arg)
			{
				pthread_create(&m_tid, NULL, thread_func, (void*)arg);
			};
		private:
			pthread_t m_tid;
			static void* thread_func(void* obj)
			{
				pthread_detach(pthread_self());
				CThread_RUN* obj1 = (CThread_RUN*)obj;
				obj1->run();
			}
	};
}
#endif

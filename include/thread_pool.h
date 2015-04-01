/*************************************************************************
    > File Name: thread_pool.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Fri 27 Mar 2015 11:12:55 PM CST
 ************************************************************************/

#ifndef __THREAD_POOL
#define __THREAD_POOL
#include"thread.h"
#include<vector>
#include"queue.h"

namespace THREAD
{
	class CThread;
	class CThread_RUN;
}

namespace THREADPOOL
{
	class CThread_pool
	{
		public:
			CThread_pool(int nworkers = 10, int ncapacity = 10)
				: m_thread_pool(nworkers), m_que(ncapacity) {}
			void on(THREAD::CThread_RUN* thread_run)
			{
				if(m_flag == false)
				{
					m_flag = true;
				}
				std::vector<THREAD::CThread>::iterator iter = m_thread_pool.begin();
				for(; iter != m_thread_pool.end(); iter++)
				{
					iter->start(thread_run);
				}
			}
			void off()
			{
				if(m_flag == true)
				{
					m_flag = false;
				}
			}
			~CThread_pool() {}
			QUEUE::CQueue m_que;
		private:
			bool m_flag;
			std::vector<THREAD::CThread> m_thread_pool;
			CThread_pool(const CThread_pool& obj) {}
			CThread_pool& operator = (const CThread_pool& obj) {}
	};
}
#endif

/*************************************************************************
    > File Name: cond.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Fri 27 Mar 2015 10:10:27 PM CST
 ************************************************************************/

#ifndef _COND_H
#define _COND_H
#include<pthread.h>
#include"mutex.h"
#include"Noncopyable.h"

namespace COND
{
	class CCond:private Noncopyable
	{
		public:
			CCond(MUTEX::CMutex& mutex) : m_mutex(mutex)
			{
				if (pthread_cond_init(&m_cond, NULL) != 0)
				{
					throw std::runtime_error("cond init");
				}
			}
			void wait()
			{
				pthread_cond_wait(&m_cond, &m_mutex.m_mutex);
			}
			void notify()
			{
				pthread_cond_signal(&m_cond);
			}
			void notifyall()
			{
				pthread_cond_broadcast(&m_cond);
			}
			~CCond()
			{
				pthread_cond_destroy(&m_cond);
			}
		private:
			MUTEX::CMutex& m_mutex;
			pthread_cond_t m_cond;
	};
}

#endif

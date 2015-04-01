/*************************************************************************
    > File Name: queue.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Fri 27 Mar 2015 10:17:31 PM CST
 ************************************************************************/

#ifndef __QUE_H
#define __QUE_H
#include"mutex.h"
#include"cond.h"
#include<queue>
#include<iostream>

namespace QUEUE
{
	class CQueue
	{
		public:
			class CTask
			{
				public:
					virtual void execute() = 0;
			};
			class CPtask 
			{
				public:
					CPtask(CTask* ptr = NULL) : m_ptr(ptr) {}
					CTask* operator -> ()
					{
						return m_ptr;
					}
					CTask&  operator * ()
					{
						return *m_ptr;
					}

				private:
					CTask* m_ptr;
			};
			CQueue(int capacity = 10) : 
				m_capacity(capacity),
				m_mutex(),
				m_pro(m_mutex),
				m_con(m_mutex),
				m_flag(true) {}
			~CQueue() {}

			bool consume(CPtask* task)
			{
				m_mutex.lock();
				std::cout << "--con has locked--" << std::endl;
				while (m_flag && m_que.empty())
				{
					m_con.wait();
				}
				if (!m_flag)
				{
					m_con.notifyall();
					return false;
				}
				*task = m_que.front();
				std::cout << "queue consume task" << std::endl;
				m_que.pop();
				m_mutex.unlock();
				m_con.notifyall();
				std::cout << "-----con pop------" << std::endl;
				return true;
			}
			bool produce(CPtask task)
			{
				std::cout << "---pro start wait--" << std::endl;
				m_mutex.lock();
				std::cout << "lock" << std::endl;
				while (m_flag && m_que.size() >= m_capacity)
				{
					std::cout << "waiting..." << std::endl;
					m_pro.wait();
				}
				if (!m_flag)
				{
					m_pro.notifyall();
					return false;
				}
				m_que.push(task);
				m_mutex.unlock();
				m_pro.notifyall();
				std::cout << "---pro notifyall---" << std::endl;
				return true;
			}
		private:
			CQueue(const CQueue& obj);
			CQueue& operator = (const CQueue& obj);
			MUTEX::CMutex m_mutex;
			COND::CCond m_pro, m_con;
			bool m_flag;
			int m_capacity;
			std::queue<CPtask> m_que;
	};
}

#endif

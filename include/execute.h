/*************************************************************************
    > File Name: execute.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Fri 27 Mar 2015 10:17:04 PM CST
 ************************************************************************/

#ifndef __FUNC_H
#define __FUNC_H
#include"thread_pool.h"
#include"text.h"
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<map>

using std::map;
using std::string;
using std::cout;
using std::endl;

namespace QUEUQE
{
	class CTask;
	class CPtask;
}

namespace EXECUTE
{
	class CThread_execute : public QUEUE::CQueue::CTask
	{
		public:
			CThread_execute(string val, Text& text) : m_val(val), m_text(text) {}
			CThread_execute(Text& text) : m_text(text) {}
			void execute()
			{
				cout << "search " << m_val <<  " result is " << endl;
				m_text.show();
			}

		private:
			string m_val;
			Text& m_text;
	};
	
	class CRun : public THREAD::CThread_RUN
	{
		public:
			CRun(QUEUE::CQueue* pq) : m_pq(pq) {}
			
			void run()
			{
				//while(1)
				//{
					QUEUE::CQueue::CPtask task;
					if (m_pq->consume(&task) == false)
					{
						cout << "false" << endl;
						return ;
					}
					task->execute();
					sleep(1);
				//}
			}
		private:
			QUEUE::CQueue* m_pq;

	};
}
#endif

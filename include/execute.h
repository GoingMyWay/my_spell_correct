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
#include"min_edict_dist.h"
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
			string execute()
			{
				cout << "search " << m_val <<  " result is " << endl;
				m_text.show();
				int min_dist;
				int dist;
				string min_res;
				map<string, int>::iterator iter = m_text.get_map().begin();
				while(iter != m_text.get_map().end())
				{
					if(iter == m_text.get_map().begin())
					{
						int min_dist = Cal_dist((*iter).first.c_str(), (*iter).first.size(), m_val.c_str(), m_val.size());
						min_res = (*iter).first;
					}
					dist = Cal_dist((*iter).first.c_str(), (*iter).first.size(), m_val.c_str(), m_val.size());
					if(dist <= min_dist)
					{
						min_res = (*iter).first;
						min_dist = dist;
					}
					cout << (*iter).first << " " << m_val << " " <<  "min_res = " << min_res << " " << "min_dist = " << min_dist << endl;
					++iter;
				}
				return min_res;
			}

		private:
			string m_val;
			Text& m_text;
	};

	class CRun : public THREAD::CThread_RUN
	{
		public:
			CRun(QUEUE::CQueue* pq) : m_pq(pq) {}

			string run()
			{
				//while(1)
				//{
				QUEUE::CQueue::CPtask task;
				if (m_pq->consume(&task) == false)
				{
					cout << "false" << endl;
					//return ;
				}
				return task->execute();
				sleep(1);
				//}
			}
		private:
			QUEUE::CQueue* m_pq;

	};
}
#endif

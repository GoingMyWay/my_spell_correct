/*************************************************************************
  > File Name: text.h
  > Author: Alexander
  > Mail: scutqiuwei@163.com 
  > Created Time: Tue 31 Mar 2015 08:43:45 AM CST
 ************************************************************************/

#ifndef _TEXT_H
#define _TEXT_H
#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include<stdlib.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::make_pair;
using std::pair;
using std::map;
using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::multimap;

class Text
{
	public:
		Text(string filepath) : ifs_(filepath.c_str()) {}

		~Text()
		{
			ifs_.close();
		}

		bool init()	
		{
			string word_;
			if(!ifs_.good())
			{
				cout << "open file failed" << endl;
				exit(-1);
			}
			while(ifs_ >> word_)
			{
				pair<map<string, int>::iterator, bool> ret
					= w_c_.insert(make_pair(word_, 1));
				if(!ret.second)
				{
					++ret.first->second;
				}
			}
			return true;
		}

		void show()
		{
			map<string, int>::iterator iter = w_c_.begin();
			while(iter != w_c_.end())
			{
				cout << (*iter).first << "\t" << (*iter).second << endl;
				++iter;
			}
		}

		map<string, int>& get_map()
		{
			return w_c_;
		}

	private:
		map<string, int> w_c_;
		ifstream ifs_;
};

#endif

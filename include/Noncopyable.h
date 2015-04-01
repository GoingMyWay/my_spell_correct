/*************************************************************************
    > File Name: Noncopyable.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Mon 30 Mar 2015 09:41:08 AM CST
 ************************************************************************/

#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class Noncopyable
{
	protected:
		Noncopyable() {}
		~Noncopyable() {}
	private:
		Noncopyable(const Noncopyable&);
		Noncopyable &operator = (const Noncopyable&);
};

#endif

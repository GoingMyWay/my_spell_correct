/*************************************************************************
    > File Name: InetAddress.h
    > Author: Alexander
    > Mail: scutqiuwei@163.com 
    > Created Time: Mon 30 Mar 2015 09:43:41 AM CST
 ************************************************************************/

#ifndef INET_ADDRESS_H
#define INET_ADDRESS_H
#include<string>
#include<netinet/in.h>
using std::string;

typedef struct sockaddr SA;
typedef struct sockaddr_in SAI;

class InetAddress
{
	public:
		explicit InetAddress(uint16_t port);
		InetAddress(const string &ip, uint16_t port);
		InetAddress(const struct sockaddr_in &addr);
		
		void setSockAddrInet(const struct sockaddr_in &addr)
		{
			addr_ = addr;
		}
		const struct sockaddr_in* getSockAddrInet() const
		{
			return &addr_;
		}

		string toIp() const;
		uint16_t toPort() const;
	private:
		struct sockaddr_in addr_;
};

#endif

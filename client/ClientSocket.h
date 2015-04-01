/*************************************************************************
  > File Name: ClientSocket.h
  > Author: Alexander
  > Mail: scutqiuwei@163.com 
  > Created Time: Mon 30 Mar 2015 02:37:06 PM CST
 ************************************************************************/

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
class InetAddress;

class ClientSocket
{
	public:
		ClientSocket();
		~ClientSocket();

		void init(int protocol);
		void connect(InetAddress& );
		int get_socket() const;

	private:
		int sockfd_;
};

#endif

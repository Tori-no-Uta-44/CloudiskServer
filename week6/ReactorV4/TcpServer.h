//
// Created by 李勃鋆 on 24-9-20.
//

#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "Acceptor.h"
#include "EventLoop.h"

namespace ReactorV4 {

	class TcpServer {
	public:
		TcpServer(const string &ip, uint16_t port);

		void start();

		void setAllCallback(TcpConnectionCallback &&newConnection, TcpConnectionCallback &&message,
		                    TcpConnectionCallback &&closeConnection);

		void stop();

		~TcpServer();

	private:
		Acceptor _acceptor;
		EventLoop _loop;
	};

} // ReactorV4

#endif //TCPSERVER_H

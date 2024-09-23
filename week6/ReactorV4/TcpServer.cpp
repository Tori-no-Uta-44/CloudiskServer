//
// Created by 李勃鋆 on 24-9-20.
//

#include "TcpServer.h"

namespace ReactorV4 {
	TcpServer::TcpServer(const string &ip, uint16_t port):
		_acceptor(ip, port), _loop(_acceptor) {
		_acceptor.setSocketOptions();
		_acceptor.binding();
		_acceptor.listening();
	}

	void TcpServer::start() {
		_loop.loop();
	}

	void TcpServer::setAllCallback(TcpConnectionCallback &&newConnection, TcpConnectionCallback &&message,
	                               TcpConnectionCallback &&closeConnection) {
		_loop.setNewConnectionCallback(std::move(newConnection));
		_loop.setMessageCallback(std::move(message));
		_loop.setCloseCallback(std::move(closeConnection));
	}

	void TcpServer::stop() {
		_loop.unLoop();
	}

	TcpServer::~TcpServer() = default;
} // ReactorV4

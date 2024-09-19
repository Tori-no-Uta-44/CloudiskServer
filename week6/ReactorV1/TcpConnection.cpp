//
// Created by 李勃鋆 on 24-9-18.
//

#include "TcpConnection.h"

namespace ReactorV1 {
	TcpConnection::TcpConnection(int socketFd):
		_socket(socketFd), _localAddr(getLocalAddress()), _peerAddr(getPeerAddress()),_socketIO(socketFd) {
	}

	string TcpConnection::receiveMessage() {
		char buffer[1024]={};
		_socketIO.readLine(buffer,1024);
	}

	void TcpConnection::sendMessage(const string &message) {
		_socketIO.sendn(message.c_str(),message.size());
	}

	void TcpConnection::toString() const {
		cout << _localAddr.getIp() << ":" << _localAddr.getPort() << "~" << _peerAddr.getIp() << ":" << _peerAddr.
			getPort() << endl;
	}

	TcpConnection::~TcpConnection() = default;

	InetAddress TcpConnection::getLocalAddress() const {
		sockaddr_in localAddr{};
		socklen_t len = sizeof(sockaddr);
		if (getsockname(_socket.get_socket_fd(), reinterpret_cast<sockaddr *>(&localAddr), &len) == -1) {
			cerr << "getsockname() error" << endl;
			_exit(-1);
		}
		return InetAddress(localAddr);
	}

	InetAddress TcpConnection::getPeerAddress() const {
		sockaddr_in peerAddr{};
		socklen_t len = sizeof(sockaddr);
		if (getpeername(_socket.get_socket_fd(), reinterpret_cast<sockaddr *>(&peerAddr), &len) == -1) {
			cerr << "getpeername() error" << endl;
			_exit(-1);
		}
		return InetAddress(peerAddr);
	}
} // ReactorV1

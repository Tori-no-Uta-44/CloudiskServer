//
// Created by 李勃鋆 on 24-9-18.
//

#include "TcpConnection.h"

namespace ReactorV2 {

	TcpConnection::TcpConnection(int socketFd) :
		_socket(socketFd),
		_localAddr(getLocalAddress()),
		_peerAddr(getPeerAddress()),
		_socketIO(socketFd) {
	}

	std::string TcpConnection::receiveMessage() const {
		char buffer[1024] = {};
		_socketIO.readLine(buffer, sizeof(buffer));
		return {buffer};
	}

	void TcpConnection::sendMessage(const std::string &message) {
		_socketIO.sendn(message.c_str(), message.size());
	}

	void TcpConnection::toString() const {
		std::cout << _localAddr.getIp() << ":" << _localAddr.getPort()
			<< " ~ " << _peerAddr.getIp() << ":" << _peerAddr.getPort()
			<< std::endl;
	}

	void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &callback) {
		_onNewConnection = callback;
		cout<<"setNewConnectionCallback &"<<endl;
	}

	void TcpConnection::invokeNewConnectionCallback() {
		if (_onNewConnection) {
			_onNewConnection(shared_from_this());
		}
		else {
			std::cout << "TcpConnection::invokeNewConnectionCallback()" << std::endl;
		}
	}

	void TcpConnection::setMessageCallback(const TcpConnectionCallback &callback) {
		_onMessage = callback;
		cout<<"setMessageCallback &"<<endl;
	}

	void TcpConnection::invokeMessageCallback() {
		if (_onMessage) {
			_onMessage(shared_from_this());
		}
		else {
			std::cout << "TcpConnection::invokeMessageCallback()" << std::endl;
		}
	}

	void TcpConnection::setCloseCallback(const TcpConnectionCallback &callback) {
		_onClose = callback;
		cout<<"setCloseCallback &"<<endl;
	}

	void TcpConnection::invokeCloseCallback() {
		if (_onClose) {
			_onClose(shared_from_this());
		}
		else {
			std::cout << "TcpConnection::invokeCloseCallback()" << std::endl;
		}
	}

	bool TcpConnection::isClosed() const {
		char buffer[16] = {};
		return recv(_socket.get_socket_fd(), buffer, sizeof(buffer), MSG_PEEK) == 0;
	}

	TcpConnection::~TcpConnection() = default;

	InetAddress TcpConnection::getLocalAddress() const {
		sockaddr_in localAddr{};
		socklen_t len = sizeof(sockaddr_in);
		if (getsockname(_socket.get_socket_fd(), reinterpret_cast<sockaddr *>(&localAddr), &len) == -1) {
			throw std::runtime_error("getsockname() error");
		}
		return InetAddress(localAddr);
	}

	InetAddress TcpConnection::getPeerAddress() const {
		sockaddr_in peerAddr{};
		socklen_t len = sizeof(sockaddr_in);
		if (getpeername(_socket.get_socket_fd(), reinterpret_cast<sockaddr *>(&peerAddr), &len) == -1) {
			throw std::runtime_error("getpeername() error");
		}
		return InetAddress(peerAddr);
	}

} // namespace ReactorV2

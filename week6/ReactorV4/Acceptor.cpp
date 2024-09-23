//
// Created by 李勃鋆 on 24-9-18.
//

#include "Acceptor.h"

namespace ReactorV4 {
	Acceptor::Acceptor(const string &ip, uint16_t port):
		_address(ip, port) {
	}

	void Acceptor::setSocketOptions() {
		int reuse = 1;
		if (setsockopt(_socket.get_socket_fd(), SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
			throw std::runtime_error("setsockopt SO_REUSEADDR failed: " + std::string(std::strerror(errno)));
		}
#ifdef SO_REUSEPORT
		if (setsockopt(_socket.get_socket_fd(), SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
			throw std::runtime_error("setsockopt SO_REUSEPORT failed: " + std::string(std::strerror(errno)));
		}
#endif
	}


	void Acceptor::binding() {
		if (bind(_socket.get_socket_fd(), reinterpret_cast<sockaddr *>(_address.getAddress()),
		         sizeof(sockaddr)) == -1) {
			cerr << "bind failed" << endl;
			_exit(-1);
		}
	}

	void Acceptor::listening() const {
		if (listen(_socket.get_socket_fd(),SOMAXCONN) == -1) {
			cerr << "listen failed" << endl;
			_exit(-1);
		}
	}

	int Acceptor::accepting() const {
		int ret = accept(_socket.get_socket_fd(), nullptr, nullptr);
		if (ret == -1) {
			cerr << "accept failed" << endl;
			_exit(-1);
		}
		return ret;
	}

	int Acceptor::getFd() const {
		return _socket.get_socket_fd();
	}

	Acceptor::~Acceptor() = default;
}

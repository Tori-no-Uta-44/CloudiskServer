//
// Created by 李勃鋆 on 24-9-18.
//

#include "Acceptor.h"

namespace ReactorV1 {
	Acceptor::Acceptor(const string &ip, uint16_t port):
		_socket(), _address(ip, port) {

	}

	void Acceptor::reSet() {
		int reuse1 = 1, reuse2 = 1;
		if (setsockopt(_socket.get_socket_fd(),SOL_SOCKET,SO_REUSEADDR, &reuse1, sizeof(reuse1)) < 0) {
			cerr << "setsockopt failed" << endl;
			_exit(-1);
		}
		if (setsockopt(_socket.get_socket_fd(),SOL_SOCKET,SO_REUSEPORT, &reuse2, sizeof(reuse2)) < 0) {
			cerr << "setsockopt failed" << endl;
			_exit(-1);
		}
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

	void Acceptor::accepting() const {
		if (accept(_socket.get_socket_fd(), nullptr, nullptr) == -1) {
			cerr << "accept failed" << endl;
			_exit(-1);
		}
	}

	Acceptor::~Acceptor() = default;
} // ReactorV1

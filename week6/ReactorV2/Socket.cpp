//
// Created by 李勃鋆 on 24-9-18.
//

#include "Socket.h"

namespace ReactorV2 {
	Socket::Socket():_socketFd(socket(AF_INET,SOCK_STREAM,0)) {
		if(_socketFd<0) {
			cerr << "Error opening socket" << endl;
			throw std::runtime_error("Socket creation failed");
		}
	}

	Socket::Socket(int socketFd):_socketFd(socketFd) {
		if(_socketFd==-1) {
			throw std::invalid_argument("Invalid socket file descriptor");
		}
	}

	int Socket::get_socket_fd() const {
		return _socketFd;
	}

	Socket::~Socket() {
		close(_socketFd);
	}
} // ReactorV1
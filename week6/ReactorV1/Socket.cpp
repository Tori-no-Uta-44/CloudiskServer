//
// Created by 李勃鋆 on 24-9-18.
//

#include "Socket.h"

namespace ReactorV1 {
	Socket::Socket():_socketFd(socket(AF_INET,SOCK_STREAM,0)) {
		if(_socketFd<0) {
			cerr << "Error opening socket" << endl;
			return;
		}
	}

	Socket::Socket(int socketFd):_socketFd(socketFd) {
	}

	int Socket::get_socket_fd() const {
		return _socketFd;
	}

	Socket::~Socket() {
		close(_socketFd);
	}
} // ReactorV1
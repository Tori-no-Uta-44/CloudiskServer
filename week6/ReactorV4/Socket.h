//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef SOCKET_H
#define SOCKET_H
#include "../../week01.h"
#include "../../func.h"

namespace ReactorV4 {

	class Socket {
	public:
		Socket();

		explicit Socket(int socketFd);

		[[nodiscard]] int get_socket_fd() const;

		~Socket();

	private:
		int _socketFd;
	};

}

#endif //SOCKET_H

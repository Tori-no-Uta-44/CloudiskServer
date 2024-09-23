//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef SOCKETIO_H
#define SOCKETIO_H
#include "../../func.h"
#include "../../week01.h"
namespace ReactorV4 {

	class SocketIO {
	public:
		explicit SocketIO(int socket);
		int recvn(void *buf,int len) const;
		int sendn(const char *buf,int len) const;
		int readLine(char *buf,int len) const;
		~SocketIO();
	private:
		int _socket;
	};

}

#endif //SOCKETIO_H

//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "../../func.h"
#include "../../week01.h"
namespace ReactorV1 {

	class TcpConnection {
	public:
		explicit TcpConnection(int socketFd);

		string receiveMessage();

		void sendMessage(const string &message);

		void toString() const;

		~TcpConnection();

	private:
		[[nodiscard]] InetAddress getLocalAddress() const;

		[[nodiscard]] InetAddress getPeerAddress() const;

		Socket _socket;
		InetAddress _localAddr;
		InetAddress _peerAddr;
		SocketIO _socketIO;
	};

} // ReactorV1

#endif //TCPCONNECTION_H

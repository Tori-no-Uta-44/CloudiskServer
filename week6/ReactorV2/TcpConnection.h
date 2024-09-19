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

namespace ReactorV2 {
	class TcpConnection;
	using TcpConnectionPrt = shared_ptr<TcpConnection>;
	using TcpConnectionCallback = function<void(const TcpConnectionPrt&)>;

	class TcpConnection : public enable_shared_from_this<TcpConnection> {
	public:
		explicit TcpConnection(int socketFd);

		string receiveMessage() const;

		void sendMessage(const string& message);

		void toString() const;

		void setNewConnectionCallback(const TcpConnectionCallback& callback);

		void invokeNewConnectionCallback();

		void setMessageCallback(const TcpConnectionCallback& callback);

		void invokeMessageCallback();

		void setCloseCallback(const TcpConnectionCallback& callback);

		void invokeCloseCallback();

		bool isClosed() const;

		~TcpConnection();

	private:
		[[nodiscard]] InetAddress getLocalAddress() const;

		[[nodiscard]] InetAddress getPeerAddress() const;

		Socket _socket;
		InetAddress _localAddr;
		InetAddress _peerAddr;
		SocketIO _socketIO;
		TcpConnectionCallback _onNewConnection;
		TcpConnectionCallback _onMessage;
		TcpConnectionCallback _onClose;
	};
} // ReactorV1

#endif //TCPCONNECTION_H

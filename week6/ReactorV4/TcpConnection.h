//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"
#include "../../func.h"
#include "../../week01.h"

namespace ReactorV4 {
	class TcpConnection;
	class EventLoop;
	using TcpConnectionPtr = shared_ptr<TcpConnection>;
	using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;

	class TcpConnection : public enable_shared_from_this<TcpConnection> {
	public:
		explicit TcpConnection(int socketFd, EventLoop* loop);

		string receiveMessage();

		void sendMessage(const string& message);

		void toString() const;

		void setNewConnectionCallback(const TcpConnectionCallback& callback);

		void invokeNewConnectionCallback();

		void setMessageCallback(const TcpConnectionCallback& callback);

		void invokeMessageCallback();

		void setCloseCallback(const TcpConnectionCallback& callback);

		void invokeCloseCallback();

		bool isClosed() const;

		void sendInLoop(const string& msg);

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
		//v4
		EventLoop* _loop;
	};
}

#endif //TCPCONNECTION_H

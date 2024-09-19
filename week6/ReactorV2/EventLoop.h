//
// Created by 李勃鋆 on 24-9-19.
//

#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include "Acceptor.h"
#include "TcpConnection.h"
#include "../../func.h"
#include "../../week01.h"

namespace ReactorV2 {

	class EventLoop {
	public:
		using TcpConnectionPrt = shared_ptr<TcpConnection>;
		using TcpConnectionCallback = function<void(const TcpConnectionPrt &)>;

		explicit EventLoop(Acceptor &acceptor);

		void loop();

		void unLoop();

		void setNewConnectionCallback(TcpConnectionCallback &&callback);

		void setMessageCallback(TcpConnectionCallback &&callback);

		void setCloseCallback(TcpConnectionCallback &&callback);

		~EventLoop();

	private:
		void waitEpollFd();

		void handleNewConnection();

		void handleMessage(int fd);

		int createEpollFd();

		void addEpollReadFd(int fd) const;

		void delEpollReadFd(int fd) const;

		int _epfd;
		vector<epoll_event> _events;
		bool _isLooping;
		Acceptor &_acceptor;
		map<int, shared_ptr<TcpConnection>> _connections;
		TcpConnectionCallback _onNewConnection;
		TcpConnectionCallback _onMessage;
		TcpConnectionCallback _onClose;
	};

} // ReactorV2

#endif //EVENTLOOP_H

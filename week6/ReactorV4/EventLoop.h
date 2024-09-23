//
// Created by 李勃鋆 on 24-9-19.
//

#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include "Acceptor.h"
#include "TcpConnection.h"
#include "../../func.h"
#include "../../week01.h"

namespace ReactorV4 {
	class TcpConnection;
	using Functor = function<void()>;

	class EventLoop {
	public:
		using TcpConnectionPtr = shared_ptr<TcpConnection>;
		using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;

		explicit EventLoop(Acceptor &acceptor);

		void loop();

		void unLoop();

		void setNewConnectionCallback(TcpConnectionCallback &&callback);

		void setMessageCallback(TcpConnectionCallback &&callback);

		void setCloseCallback(TcpConnectionCallback &&callback);
		//V4
		void wakeup();
		void doPendingFunctors();
		void runInLoop(Functor &&cd);
		~EventLoop();

	private:
		void waitEpollFd();

		void handleNewConnection();

		void handleMessage(int fd);

		int createEpollFd();

		void addEpollReadFd(int fd);

		void delEpollReadFd(int fd);
		//v4
		void handleRead();
		int createEventFd();
		int _epfd;
		vector<epoll_event> _events;
		bool _isLooping;
		Acceptor &_acceptor;
		map<int, shared_ptr<TcpConnection>> _connections;
		TcpConnectionCallback _onNewConnection;
		TcpConnectionCallback _onMessage;
		TcpConnectionCallback _onClose;
		int _evtfd;
		vector<Functor> _pending;
		mutex _mutex;
	};

}

#endif //EVENTLOOP_H

//
// Created by 李勃鋆 on 24-9-19.
//

#include "EventLoop.h"

namespace ReactorV4 {
	EventLoop::EventLoop(Acceptor &acceptor):
		_epfd(createEpollFd()), _events(1024), _isLooping(false), _acceptor(acceptor), _evtfd(createEventFd()) {
		addEpollReadFd(_acceptor.getFd());
		addEpollReadFd(_evtfd);
	}

	void EventLoop::loop() {
		_isLooping = true;
		while (_isLooping) {
			waitEpollFd();
		}
	}

	void EventLoop::unLoop() {
		_isLooping = false;
		wakeup();
	}

	void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&callback) {
		_onNewConnection = move(callback);
		cout << "setNewConnectionCallback &&" << endl;
	}

	void EventLoop::setMessageCallback(TcpConnectionCallback &&callback) {
		_onMessage = move(callback);
		cout << "setMessageCallback &&" << endl;
	}

	void EventLoop::setCloseCallback(TcpConnectionCallback &&callback) {
		_onClose = move(callback);
		cout << "setCloseCallback &&" << endl;
	}

	void EventLoop::wakeup() {
		uint64_t one = 1;
		if (send(_evtfd, &one, sizeof(one), 0) != sizeof(uint64_t)) {
			throw std::runtime_error("send EventLoop::wakeup()" + std::string(std::strerror(errno)));
		}
	}

	void EventLoop::doPendingFunctors() {
		vector<Functor> t;
		unique_lock<mutex> lock(_mutex);
		t.swap(_pending);
		lock.unlock();
		for (auto &cb : t) {
			cb();
		}
	}

	void EventLoop::runInLoop(Functor &&cd) {
		unique_lock<mutex> lock(_mutex);
		_pending.emplace_back(cd);
		lock.unlock();
		wakeup();
	}

	void EventLoop::handleRead() {
		uint64_t s = 1;
		if (recv(_evtfd, &s, sizeof(s), 0) != sizeof(uint64_t)) {
			throw std::runtime_error("recv EventLoop::handleRead()" + std::string(std::strerror(errno)));
		}
	}

	int EventLoop::createEventFd() {
		int efd = eventfd(0, 0);
		if (efd == -1) {
			throw std::runtime_error("eventfd failed" + std::string(std::strerror(errno)));
		}
		return efd;
	}

	EventLoop::~EventLoop() {
		close(_epfd);
		close(_evtfd);
	}

	void EventLoop::waitEpollFd() {
		//3
		int num;
		do {
			num = epoll_wait(_epfd, &_events[0], static_cast<int>(_events.size()), -1);
		}
		while (num == -1 && errno == EINTR);
		if (num == -1) {
			throw std::runtime_error("epoll_wait error" + std::string(std::strerror(errno)));
		}
		if (num == 0) {
			std::cerr << "epoll_wait timeout" << std::endl;
		}
		else {
			if (num == static_cast<int>(_events.size())) {
				_events.resize(2 * _events.size());
			}
			for (int i = 0; i < num; i++) {
				if (_events[i].data.fd == _acceptor.getFd()) {
					if(_events[i].events&EPOLLIN) {
						handleNewConnection();
					}
				}else if(_events[i].data.fd==_evtfd) {
					if(_events[i].events&EPOLLIN) {
						handleRead();
						doPendingFunctors();
					}
				}
				else {
					if (_events[i].events & EPOLLIN) {
						handleMessage(_events[i].data.fd);
					}
				}
			}
		}
	}

	void EventLoop::handleNewConnection() {
		int fd = _acceptor.accepting();
		if (fd == -1) {
			std::cerr << "accept error" << std::endl;
			return;
		}
		addEpollReadFd(fd);
		// TcpConnectionPtr con(new TcpConnection(fd, this));
		TcpConnectionPtr con(make_shared<TcpConnection>(fd, this));
		con->setNewConnectionCallback(_onNewConnection);
		con->setMessageCallback(_onMessage);
		con->setCloseCallback(_onClose);
		_connections[fd] = con;
		con->invokeNewConnectionCallback();
	}

	void EventLoop::handleMessage(int fd) {
		auto it = _connections.find(fd);
		if (it != _connections.end()) {
			if (it->second->isClosed()) {
				it->second->invokeCloseCallback();
				delEpollReadFd(fd);
				_connections.erase(it);
			}
			else {
				it->second->invokeMessageCallback();
			}
		}
		else {
			std::cerr << "fd " << fd << " doesn't exist" << std::endl;
		}
	}

	int EventLoop::createEpollFd() {
		//1
		int epfd = epoll_create1(0);
		if (epfd == -1) {
			cerr << "epfd create fail" << endl;
			return -1;
		}
		return epfd;
	}

	void EventLoop::addEpollReadFd(const int fd) {
		//2
		epoll_event event{};
		event.events = EPOLLIN;
		event.data.fd = fd;
		if (epoll_ctl(_epfd,EPOLL_CTL_ADD, fd, &event) == -1) {
			cerr << "epoll_ctl fail" << endl;
		}
	}

	void EventLoop::delEpollReadFd(const int fd) {
		//最后
		epoll_event event{};
		event.events = EPOLLIN;
		event.data.fd = fd;
		if (epoll_ctl(_epfd,EPOLL_CTL_DEL, fd, &event) == -1) {
			cerr << "epoll_ctl fail" << endl;
		}
	}
}

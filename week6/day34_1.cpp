//
// Created by 李勃鋆 on 24-9-20.
//
#include "../week01.h"
#include "../week6.h"
#include "ReactorV4/TcpServer.h"
#include "ReactorV4/Tasks.h"
#include "ReactorV4/ThreadPool.h"
#include "ReactorV4/TcpConnection.h"
ReactorV4::ThreadPool *gPool = nullptr;

void onNewConnection(const ReactorV4::TcpConnectionPtr &con) {
	cout << "onNewConnection";
	con->toString();
}

void onMessage(const ReactorV4::TcpConnectionPtr &con) {
	string msg = con->receiveMessage();
	cout << msg << endl;
	gPool->setTask(std::make_unique<ReactorV4::RectangleTask>(con));
	gPool->setTask(std::make_unique<ReactorV4::CircleTask>(con));
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void onClose(const ReactorV4::TcpConnectionPtr &con) {
	cout << "Close connection";
	con->toString();
}

void test34_1() {
	using namespace ReactorV4;
	ThreadPool thread_pool(4, 8);
	thread_pool.run();
	gPool = &thread_pool;
	TcpServer server("192.168.5.240", 8081);
	server.setAllCallback(onNewConnection, onMessage, onClose);
	server.start();
}

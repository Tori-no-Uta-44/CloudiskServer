//
// Created by 李勃鋆 on 24-9-19.
//
#include "../week01.h"
#include "../week6.h"
#include "ReactorV2/Acceptor.h"
#include "ReactorV2/EventLoop.h"
void onNewConnection(const ReactorV2::TcpConnectionPrt &con) {
	cout << "onNewConnection";
	con->toString();
}
void onMessage(const ReactorV2::TcpConnectionPrt &con) {
	string msg=con->receiveMessage();
	cout << msg << endl;
	con->sendMessage(msg);
}
void onClose(const ReactorV2::TcpConnectionPrt &con) {
	cout << "Close connection";
	con->toString();
}
void test33_1() {
	using namespace ReactorV2;
	Acceptor acceptor("192.168.5.240",8081);
	acceptor.reSet();
	acceptor.binding();
	acceptor.listening();
	EventLoop loop(acceptor);
	loop.setNewConnectionCallback(move(onNewConnection));
	loop.setMessageCallback(move(onMessage));
	loop.setCloseCallback(move(onClose));
	loop.loop();
}

//
// Created by 李勃鋆 on 24-10-10.
//
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include "../week01.h"
struct MQinfo{
	string Exchange = "demo_exchange";
	string Queue = "demo_queue";
	string RoutingKey = "key0";
};
int test_rabbitmq(){
	MQinfo info;
	// 1 建立通信的连接channel
	// AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create();
	auto *opts=new AmqpClient::Channel::OpenOpts();
	opts->host="127.0.0.1";
	opts->port=5672;
	opts->vhost="/";
	AmqpClient::Channel::OpenOpts::BasicAuth auth("guest", "guest");
	opts->auth=auth;
	AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Open(*opts);
	// 2 设置好消息
	AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create(R"({"filename":"tmp/BB.cpp"})");
	// 3 通过channel去发布消息
	channel->BasicPublish(info.Exchange,info.RoutingKey,message);
	delete opts;
	return 0;
}

//
// Created by 李勃鋆 on 24-10-5.
//
#include <WFFacilities.h>
#include <csignal>
#include <iostream>
#include <string>
#include "../week6.h"
using namespace std;
static WFFacilities::WaitGroup wait_group(1);
struct RedisBuffer {
	string data;
};
void sigint_handler(int sig) {
	wait_group.done();
	cout << "done" << endl;
}

void get_callback(WFRedisTask *redis_task) {
	protocol::RedisRequest *request = redis_task->get_req();
	protocol::RedisResponse *response = redis_task->get_resp();
	int state = redis_task->get_state();
	int error = redis_task->get_error();
	protocol::RedisValue redis_value;
	switch (state) {
	case WFT_STATE_SYS_ERROR:
		fprintf(stderr, "system error: %s\n", strerror(error));
		break;
	case WFT_STATE_DNS_ERROR:
		fprintf(stderr, "DNS error: %s\n", gai_strerror(error));
		break;
	case WFT_STATE_SSL_ERROR:
		fprintf(stderr, "SSL error: %d\n", error);
		break;
	case WFT_STATE_TASK_ERROR:
		fprintf(stderr, "Task error: %d\n", error);
		break;
	case WFT_STATE_SUCCESS:
		response->get_result(redis_value);
		if (redis_value.is_error()) {
			fprintf(stderr, "%*s\n", static_cast<int>(redis_value.string_view()->size()),
			        redis_value.string_view()->c_str());
			state = WFT_STATE_TASK_ERROR;
		}
		break;
	}
	if (state != WFT_STATE_SUCCESS) {
		fprintf(stderr, "Failed. Press Ctrl-C to exit.\n");
		return;
	}
	//5.判断是字符串还是数组
	if (redis_value.is_string()) {
		cout << redis_value.string_value() << endl;
		//11.修改容器里面的值
		auto *buffer = static_cast<RedisBuffer *>(series_of(redis_task)->get_context());
		buffer->data = redis_value.string_value();
		//6.动态的添加序列
		if (redis_value.string_value() == "value") {
			WFRedisTask *new_task = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, nullptr);
			new_task->get_req()->set_request("SET", {"key", "bb"});
			//7.获取序列
			series_of(redis_task)->push_back(new_task);
		}
	}
	else if (redis_value.is_array()) {
		for (size_t i = 0; i < redis_value.arr_size(); i++) {
			cout << i << "--" << redis_value[i].string_value() << "\t";
		}
		cout << endl;
	}
}

void test_redis_workflow() {
	signal(SIGINT, sigint_handler);
	//1.添加redis任务
	WFRedisTask *redis_task = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, nullptr);
	protocol::RedisRequest *redis_request = redis_task->get_req();
	redis_request->set_request("SET", {"a", "a"});

	WFRedisTask *redis_get0 = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, get_callback);
	protocol::RedisRequest *get_request0 = redis_get0->get_req();
	get_request0->set_request("GET", {"key"});

	WFRedisTask *redis_get = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, get_callback);
	protocol::RedisRequest *get_request = redis_get->get_req();
	get_request->set_request("HGETALL", {"runoobkey"});

	//8.初始化数据共享的容器
	auto *redis_buffer = new RedisBuffer();

	//2.把定义好的任务放入序列中，设定队头
	SeriesWork *series_work = Workflow::create_series_work(redis_task, nullptr);
	//3.尾插
	series_work->push_back(redis_get0);
	series_work->push_back(redis_get);
	//9.把容器放到序列中
	series_work->set_context(redis_buffer);
	//10.设置序列的回调函数
	series_work->set_callback([redis_buffer](const SeriesWork *series_work) {
		cout<<redis_buffer->data<<endl;
		delete redis_buffer;
	});
	//4.启动
	series_work->start();
	wait_group.wait();
}

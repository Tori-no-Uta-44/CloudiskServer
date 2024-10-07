//
// Created by 李勃鋆 on 24-10-5.
//
#include <WFFacilities.h>

#include "../week01.h"

static WFFacilities::WaitGroup wait_group(1);

namespace day02_02 {
	void sigint_handler(int sig) {
		wait_group.done();
		cout << "done" << endl;
	}
	struct WebBuffer {
		string data;
	};
	void http_callback(WFHttpTask *task) {
		protocol::HttpRequest *req = task->get_req();//获取request（请求）的信息
		protocol::HttpResponse *resp = task->get_resp();//获取response（响应）的信息
		int state = task->get_state();//获取任务的状态码
		int error = task->get_error();//获取任务的错误码

		switch (state) {
		case WFT_STATE_SYS_ERROR://系统错误
			cerr << "system error: " << strerror(error) << "\n";
			break;
		case WFT_STATE_DNS_ERROR://DNS错误
			cerr << "DNS error: " << gai_strerror(error) << "\n";
			break;
		case WFT_STATE_SSL_ERROR://SSL错误
			cerr << "SSL error: " << error << "\n";
			break;
		case WFT_STATE_TASK_ERROR://任务错误
			cerr << "Task error: " << error << "\n";
			break;
		case WFT_STATE_SUCCESS://任务成功
			break;
		}
		if (state != WFT_STATE_SUCCESS) {//未成功时输出提示信息
			cerr << "Failed. Press Ctrl-C to exit.\n";
			return;
		}

		const void *body;
		size_t body_len;
		resp->get_parsed_body(&body, &body_len);
		auto *buffer=static_cast<WebBuffer*>(series_of(task)->get_context());

		// cout << static_cast<const char *>(body) << "\n";
		buffer->data=static_cast<const char *>(body);
		WFRedisTask *redis_task=WFTaskFactory::create_redis_task("redis://127.0.0.1",1,nullptr);
		redis_task->get_req()->set_request("set",{"data",buffer->data});
		series_of(task)->push_back(redis_task);
	}
}

void WF_test02_02() {
	using namespace day02_02;
	signal(SIGINT, sigint_handler);

	auto *buffer=new WebBuffer();

	WFHttpTask *http_task=WFTaskFactory::create_http_task("http://www.bilibili.com",10,10,http_callback);

	SeriesWork *series_work=Workflow::create_series_work(http_task,[buffer](const SeriesWork *series_work) {
		// cout << buffer->data << "\n";
		delete buffer;
	});
	series_work->set_context(buffer);
	series_work->start();
	wait_group.wait();
}
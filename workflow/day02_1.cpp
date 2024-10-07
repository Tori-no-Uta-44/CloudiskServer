//
// Created by 李勃鋆 on 24-10-5.
//
#include <WFFacilities.h>

#include "../week01.h"

namespace day02 {
	static WFFacilities::WaitGroup wait_group(1);

	void sigint_handler(int sig) {
		wait_group.done();
		cout << "done" << endl;
	}

	struct RedisBuffer {
		string str;
	};

	void Redis_task_callback(WFRedisTask *redis_task) {
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
		if(redis_value.is_string()) {
			if(redis_value.string_value()!="100") {
				auto *buffer=static_cast<RedisBuffer*>(series_of(redis_task)->get_context());
				buffer->str=redis_value.string_value();
				WFRedisTask *task=WFTaskFactory::create_redis_task("redis://127.0.0.1",1,Redis_task_callback);
				task->get_req()->set_request("get",{buffer->str});
				series_of(redis_task)->push_back(task);
			}
		}
	}
}

void WF_test01() {
	using namespace day02;
	signal(SIGINT, sigint_handler);
	auto *buffer = new RedisBuffer();
	WFRedisTask *redis_task = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, Redis_task_callback);
	redis_task->get_req()->set_request("get", {"x1"});

	SeriesWork *series_work = Workflow::create_series_work(redis_task, [buffer](const SeriesWork *series_work) {
		cout << buffer->str << endl;
		delete buffer;
	});
	series_work->set_context(buffer);
	series_work->start();
	wait_group.wait();
}

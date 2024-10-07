//
// Created by 李勃鋆 on 24-10-5.
//

#include <WFFacilities.h>

#include "../week01.h"

static WFFacilities::WaitGroup wait_group(1);

namespace day02_04 {
	void sigint_handler(int sig) {
		wait_group.done();
		cout << "done" << endl;
	}

	struct HttpBuffer {
		unsigned long len = 0;
		string url;
	};

	void parallel_work_callback(const ParallelWork *parallel_work) {
		string url;
		unsigned long len = 0;
		for (int i = 0; i < 2; i++) {
			const SeriesWork *series_work = parallel_work->series_at(i);
			auto *buffer = static_cast<HttpBuffer *>(series_work->get_context());
			if (len < buffer->len) {
				len = buffer->len;
				url = buffer->url;
			}
			delete buffer;
		}
		cout << url << "--" << len << endl;
	}

	void http_callback(WFHttpTask *task) {
		protocol::HttpRequest *req = task->get_req(); //获取request（请求）的信息
		protocol::HttpResponse *resp = task->get_resp(); //获取response（响应）的信息
		int state = task->get_state(); //获取任务的状态码
		int error = task->get_error(); //获取任务的错误码

		switch (state) {
		case WFT_STATE_SYS_ERROR: //系统错误
			cerr << "system error: " << strerror(error) << "\n";
			break;
		case WFT_STATE_DNS_ERROR: //DNS错误
			cerr << "DNS error: " << gai_strerror(error) << "\n";
			break;
		case WFT_STATE_SSL_ERROR: //SSL错误
			cerr << "SSL error: " << error << "\n";
			break;
		case WFT_STATE_TASK_ERROR: //任务错误
			cerr << "Task error: " << error << "\n";
			break;
		case WFT_STATE_SUCCESS: //任务成功
			break;
		}
		if (state != WFT_STATE_SUCCESS) {
			//未成功时输出提示信息
			cerr << "Failed. Press Ctrl-C to exit.\n";
			return;
		}
		const void *body;
		size_t body_len;
		resp->get_parsed_body(&body, &body_len);
		auto *buffer = static_cast<HttpBuffer *>(series_of(task)->get_context());

		buffer->len = body_len;
	}
}

void WF_test02_04() {
	using namespace day02_04;
	signal(SIGINT, sigint_handler);
	ParallelWork *parallel_work = Workflow::create_parallel_work(parallel_work_callback);
	vector<string> urls = {"http://www.github.com/", "http://bilibili.com"};
	for (auto &url : urls) {
		WFHttpTask *http_task = WFTaskFactory::create_http_task(url, 10, 10, http_callback);
		SeriesWork *series_work = Workflow::create_series_work(http_task, nullptr);
		auto *buffer = new HttpBuffer();
		buffer->url = url;
		series_work->set_context(buffer);
		parallel_work->add_series(series_work);
	}
	parallel_work->start();
	wait_group.wait();
}

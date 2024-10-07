//
// Created by 李勃鋆 on 24-10-4.
//
// http客户端
#include <csignal>
#include <iostream>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include "../week6.h"
using std::cout;
using std::cerr;
static WFFacilities::WaitGroup waitGroup(1);//静态变量，在全局静态区，整个程序范围

void sighandler(int signum) {//信号处理函数的回调函数
	waitGroup.done();//减少waitGroup的数量，每次减少一个，为0时结束
	cout << "done\n";
}

void httpCallback(WFHttpTask *task) {
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

	cerr << req->get_method() << " "//请求的方法
		<< req->get_http_version() << " "//https的版本
		<< req->get_request_uri() << "\n";//请求的URI
	protocol::HttpHeaderCursor reqCursor(req);//请求头的迭代器
	std::string name;
	std::string value;
	while (reqCursor.next(name, value)) {//遍历输出迭代器里面的信息
		cerr << "name = " << name << " value = " << value << "\n";
	}


	cerr << resp->get_http_version() << " "//响应的版本
		<< resp->get_status_code() << " "//响应的状态码
		<< resp->get_reason_phrase() << "\n";//状态码的文字描述比如：OK，Not Found
	protocol::HttpHeaderCursor respCursor(resp);//响应头的迭代器
	while (respCursor.next(name, value)) {//遍历输出响应头的所有信息
		cerr << "name = " << name << " value = " << value << "\n";
	}

	const void *body;
	size_t body_len;
	resp->get_parsed_body(&body, &body_len);//提取解析后的响应体，并将内容的指针存储在 body 中，长度存储在 body_len 中
	cerr << static_cast<const char *>(body) << "\n";//body 是一个 void* 指针，它存储的是二进制数据，所以需要将它转换为 char* 来表示字符串
}

int testWorkflow() {
	signal(SIGINT, sighandler);//信号处理函数

	WFHttpTask *httpTask = WFTaskFactory::create_http_task(//创建一个http连接任务
		"http://www.baidu.com",//URL
		10,//重定向的最大值
		10,//最大重连次数
		httpCallback//具体执行的任务
		);

	httpTask->start();//开始任务
	waitGroup.wait();//等待任务全部完成
	cout << "finished!\n";
	return 0;
}

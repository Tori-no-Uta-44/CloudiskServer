//
// Created by 李勃鋆 on 24-10-6.
//
#include <WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include "../week01.h"
#include "../nlohmann/json.hpp"

static WFFacilities::WaitGroup wait_group(1);

namespace day03_2 {
	void sigint_handler(int sig) {
		wait_group.done();
		cout << "done" << endl;
	}

	struct HttpContext {
		string username;
		string password;
		protocol::HttpResponse *response{};
	};

	void server_callback(WFHttpTask *task) {
		cout << "serverCallback is called!\n";
		protocol::HttpResponse *resp = task->get_resp();
		std::string json_response = R"({"status": "error", "message": "Failed to parse request"})";
		resp->append_output_body(json_response);
		resp->add_header_pair("Content-Type", "application/json");
	}

	void redis_task_callback(WFRedisTask *redis_task) {
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
		auto *context = static_cast<HttpContext *>(series_of(redis_task)->get_context());
		if (redis_value.is_string()) {
			if (redis_value.string_value() == context->password) {
				std::string json_response = R"({"status": "success", "message": "Login successful!"})";
				context->response->append_output_body(json_response);
				context->response->add_header_pair("Content-Type", "application/json");
			}
			else {
				context->response->append_output_body(R"({"status": "error", "message": "Redis task failed"})");
				context->response->add_header_pair("Content-Type", "application/json");
			}
		}
	}
	std::map<std::string, std::string> parse_url_encoded(const std::string &body) {
		std::map<std::string, std::string> data;
		std::istringstream body_stream(body);
		std::string token;

		while (std::getline(body_stream, token, '&')) {
			auto delimiter_pos = token.find('=');
			std::string key = token.substr(0, delimiter_pos);
			std::string value = token.substr(delimiter_pos + 1);
			data[key] = value;
		}

		return data;
	}
	void process(WFHttpTask *task) {
		cout << "process is called!\n";
		protocol::HttpRequest *req = task->get_req(); //获取request（请求）的信息
		protocol::HttpResponse *resp = task->get_resp(); //获取response（响应）的信息

		string method = req->get_method();
		if (method == "GET") {
			std::ifstream file("/root/CLionProjects/cppDemo/workflow/postform.html");
			if (file) {
				std::stringstream buffer;
				buffer << file.rdbuf(); // 读取文件内容
				resp->append_output_body(buffer.str()); // 将内容添加到响应体中
				file.close();
			}
			else {
				resp->append_output_body("Failed to load form page.\n");
			}
		}
		else if (method == "POST") {
			const void *body;
			size_t body_len;
			req->get_parsed_body(&body, &body_len);
			// auto *buffer=static_cast<WebBuffer*>(series_of(task)->get_context());

			cout << static_cast<const char *>(body) << "\n";

			std::string body_str(static_cast<const char*>(body), body_len);

			// Parse URL-encoded data
			auto data = parse_url_encoded(body_str);
			std::string name = data["username"];
			std::string pwd = data["password"];

			auto *context = new HttpContext();
			context->username = name;
			context->password = pwd;
			context->response = resp;
			series_of(task)->set_context(context);

			// 创建 Redis 任务，检查用户名和密码
			WFRedisTask *redis_task = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, redis_task_callback);
			redis_task->get_req()->set_request("HGET", {"userinfo", name});
			series_of(task)->push_back(redis_task);

			task->set_callback(server_callback);


			// string url = req->get_request_uri();
			// string path = url.substr(0, url.find('?'));
			// string query = url.substr(url.find('?') + 1);
			// string nameKV = query.substr(0, query.find('&'));
			// string name = nameKV.substr(nameKV.find('=') + 1);
			// string pwdKV = query.substr(query.find('&') + 1);
			// string pwd = pwdKV.substr(pwdKV.find('=') + 1);
			//
			// cout << "method = " << method << "\n";
			// cout << "url = " << url << "\n";
			// cout << "path = " << path << "\n";
			// cout << "query = " << query << "\n";
			// cout << "name = " << name << "\n";
			// cout << "nameKV = " << nameKV << "\n";
			// cout << "pwdKV = " << pwdKV << "\n";
			// cout << "pwd = " << pwd << "\n";
			//
			//
			// auto *context = new HttpContext();
			// context->username = name;
			// context->password = pwd;
			// context->response = resp;
			// series_of(task)->set_context(context);
			//
			// WFRedisTask *redis_task = WFTaskFactory::create_redis_task("redis://127.0.0.1", 1, redis_task_callback);
			// redis_task->get_req()->set_request("hget", {"userinfo", name});
			// series_of(task)->push_back(redis_task);
			//
			// task->set_callback(server_callback);
		}
	}
}

void WF_test03_2() {
	signal(SIGINT, day03_2::sigint_handler);
	WFHttpServer server(day03_2::process);
	if (server.start(8081) == 0) {
		cout << "server start success!\n";
		wait_group.wait();
		server.stop();
	}
}

//
// Created by 李勃鋆 on 24-10-6.
//
#include <WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/MySQLUtil.h>
#include <workflow/MySQLResult.h>
#include "../week01.h"

static WFFacilities::WaitGroup wait_group(1);

namespace day03_1 {
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
	}

	void mysql_task_callback(WFMySQLTask *mysqlTask) {
		// 获取 HTTP 上下文
		auto *context = static_cast<HttpContext *>(series_of(mysqlTask)->get_context());

		if (mysqlTask->get_state() != WFT_STATE_SUCCESS) {
			cerr << "error_msg =  " << WFGlobal::get_error_string(mysqlTask->get_state(), mysqlTask->get_error()) << "\n";
			context->response->append_output_body("Internal error occurred.\n");
			delete context;
			return;
		}

		protocol::MySQLResponse *resp = mysqlTask->get_resp();
		if (resp->get_packet_type() == MYSQL_PACKET_ERROR) {
			cerr << "error_code = " << resp->get_error_code() << " error_msg = " << resp->get_error_msg() << "\n";
			context->response->append_output_body("Database error occurred.\n");
			delete context;
			return;
		}

		protocol::MySQLResultCursor cursor(resp);
		std::vector<std::vector<protocol::MySQLCell>> rows;
		cursor.fetch_all(rows);

		if (rows.empty()) {
			// 没有找到匹配的记录
			context->response->append_output_body("Invalid username or password.\n");
		} else {
			// 从数据库中提取 username 和 password 进行比较
			auto &row = rows[0]; // 只处理第一行数据
			string db_username = row[0].as_string();  // 假设数据库的第一列是用户名
			string db_password = row[1].as_string();  // 假设数据库的第二列是密码

			// 比较数据库中的用户名和密码与请求中的是否一致
			if (db_username == context->username && db_password == context->password) {
				context->response->append_output_body("Login successful!\n");
			} else {
				context->response->append_output_body("Invalid username or password.\n");
			}
		}

		delete context; // 清理上下文
	}


	void process(WFHttpTask *task) {
		cout << "process is called!\n";
		protocol::HttpRequest *req = task->get_req(); //获取request（请求）的信息
		protocol::HttpResponse *resp = task->get_resp(); //获取response（响应）的信息

		string method = req->get_method();
		string url = req->get_request_uri();
		string path = url.substr(0, url.find('?'));
		string query = url.substr(url.find('?') + 1);
		string nameKV = query.substr(0, query.find('&'));
		string name = nameKV.substr(nameKV.find('=') + 1);
		string pwdKV = query.substr(query.find('&') + 1);
		string pwd = pwdKV.substr(pwdKV.find('=') + 1);

		cout << "method = " << method << "\n";
		cout << "url = " << url << "\n";
		cout << "path = " << path << "\n";
		cout << "query = " << query << "\n";
		cout << "name = " << name << "\n";
		cout << "nameKV = " << nameKV << "\n";
		cout << "pwdKV = " << pwdKV << "\n";
		cout << "pwd = " << pwd << "\n";


		auto *context = new HttpContext();
		context->username = name;
		context->password = pwd;
		context->response = resp;
		series_of(task)->set_context(context);

		WFMySQLTask *mysql_task = WFTaskFactory::create_mysql_task("mysql://root:Elysian@localhost", 1,
		                                                           mysql_task_callback);
		string sql = "select * from demo.test where username='" + context->username + "' && password='" + context->
			password + "';";
		mysql_task->get_req()->set_query(sql);
		series_of(task)->push_back(mysql_task);

		task->set_callback(server_callback);
	}

}

void WF_test03_1() {
	signal(SIGINT, day03_1::sigint_handler);
	WFHttpServer server(day03_1::process);
	if (server.start(8081) == 0) {
		cout << "server start success!\n";
		wait_group.wait();
		server.stop();
	}
}

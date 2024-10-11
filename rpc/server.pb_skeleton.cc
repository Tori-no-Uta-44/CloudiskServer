#include "signin.srpc.h"
#include "workflow/WFFacilities.h"
#include <workflow/MySQLUtil.h>
#include <workflow/MySQLResult.h>
#include <crypt.h>
#include "../week01.h"
using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

class UserServiceServiceImpl : public UserService::Service
{
public:

	void Signin(ReqSignin *request, RespSignup *response, srpc::RPCContext *ctx) override
	{
		string username = request->username();
		string password = request->password();

		string salt("12345678");//这里应该是随机生成
		string encodedPassword(crypt(password.c_str(), salt.c_str()));

		string mysqlurl("mysql://root:Elysian@localhost");
		auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1,
			[response](WFMySQLTask * mysqltask){
				//0. 对任务的状态进行检测
				int state = mysqltask->get_state();
				int error = mysqltask->get_error();
				if(state != WFT_STATE_SUCCESS) {
					printf("%s\n", WFGlobal::get_error_string(state, error));
					return;
				}
				//1. SQL应用层面是否存在错误（语法、唯一键）
				auto mysqlResp = mysqltask->get_resp();
				if(mysqlResp->get_packet_type() == MYSQL_PACKET_ERROR) {
					printf("ERROR %d: %s\n", mysqlResp->get_error_code(),
						   mysqlResp->get_error_msg().c_str());
					response->set_code(101);
					response->set_information("Signup fail");
					return;
				}
				using namespace protocol;
				MySQLResultCursor cursor(mysqlResp);
				if(cursor.get_cursor_status() == MYSQL_STATUS_OK) {
					//2. 成功写入数据库了
					printf("Query OK. %llu row affected.\n",cursor.get_affected_rows());
					response->set_code(100);
					response->set_information("Signup success");
				} else {
					response->set_code(101);
					response->set_information("Signup fail");
				}
			});
		string sql("INSERT INTO cloudisk.tbl_user(user_name, user_pwd) VALUES('");
		sql += username + "', '" + encodedPassword + "')";
		mysqlTask->get_req()->set_query(sql);

		ctx->get_series()->push_back(mysqlTask);
	}
};

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	unsigned short port = 1412;
	SRPCServer server;

	UserServiceServiceImpl userservice_impl;
	server.add_service(&userservice_impl);

	server.start(port);
	wait_group.wait();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

#include "signin.srpc.h"
#include "workflow/WFFacilities.h"
#include "../week01.h"
using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo) {
	wait_group.done();
}

static void signin_done(RespSignup *response, srpc::RPCContext *context) {
	cout << "code = " << response->code()
		<< " information = " << response->information()
		<< "\n";
}

int main() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	const char *ip = "127.0.0.1";
	unsigned short port = 1412;

	UserService::SRPCClient client(ip, port);

	// example for RPC method call
	ReqSignin signin_req;
	//signin_req.set_message("Hello, srpc!");
	// client.Signin(&signin_req, signin_done);
	signin_req.set_username("admin0");
	signin_req.set_password("123");

	auto rpctask = client.create_Signin_task(signin_done);
	rpctask->serialize_input(&signin_req);
	rpctask->start();
	wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}

#include "week01.h"
#include "week02.h"
#include "week03.h"
#include "week04.h"
#include "week5.h"
#include "week6.h"

int main(int argc, char *argv[]) {
	auto beforeTime = std::chrono::steady_clock::now();
	test_rabbitmq();
	auto afterTime = std::chrono::steady_clock::now();
	double duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
	std::cout << duration_second << "秒" << std::endl;
	return 0;
}

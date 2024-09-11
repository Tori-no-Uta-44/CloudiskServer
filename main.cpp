#include "week01.h"
#include "week02.h"
#include "week03.h"
#include "week04.h"
#include "week5.h"

int main(int argc, char *argv[]) {
	auto beforeTime = std::chrono::steady_clock::now();
	test24_01();
	auto afterTime = std::chrono::steady_clock::now();
	double duration_second = std::chrono::duration<double>(afterTime - beforeTime).count();
	std::cout << duration_second << "秒" << std::endl;
	return 0;
}

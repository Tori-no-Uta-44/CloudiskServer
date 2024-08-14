#include "week01.h"

namespace my_namespace {
	int add(int a, int b) {
		return a + b;
	}

	double add(double a, int b) {
		return a + b;
	}

	double add(int a, double b = 44.0) {
		return a + b;
	}

	int add(int a, int b, int c) {
		return a + b + c;
	}
}

void test_02_02() {
	using namespace my_namespace;
	std::cout << "add(1, 2) = " << add(1, 2) << std::endl;
	std::cout << "add(1.0, 2) = " << add(1.0, 2) << std::endl;
	std::cout << "add(1, 2.0) = " << add(1, 2.0) << std::endl;
	std::cout << "add(2) = " << add(2) << std::endl;
	std::cout << "add(1, 2, 3) = " << add(1, 2, 3) << std::endl;
}

int main() {
	test_02_02();
	return 0;
}

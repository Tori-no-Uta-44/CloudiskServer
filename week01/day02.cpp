//
// Created by 李勃鋆 on 24-8-13.
//

#include "../week01.h"

void f2(int &x, int &y) {
	int z = x;
	x = y;
	y = z;
}

void f3(int *x, int *y) {
	int z = *x;
	*x = *y;
	*y = z;
}

void test_02_01() {
	int x, y;
	x = 10;
	y = 26;
	std::cout << "x,y:" << x << "," << y << std::endl;
	f2(x, y);
	std::cout << "x,y:" << x << "," << y << std::endl;
	f3(&x, &y);
	std::cout << "x,y:" << x << "," << y << std::endl;
	x++;
	y--;
	f2(y, x);
	std::cout << "x,y:" << x << "," << y << std::endl;
}

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

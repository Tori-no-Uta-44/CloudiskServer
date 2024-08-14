//
// Created by 李勃鋆 on 24-8-13.
//

#include "week01.h"

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

//
// Created by 李勃鋆 on 24-8-20.
//
#include "../week02.h"

class Point_test_08_04;

class Line_test_08_04 {
public:
	double distance(Point_test_08_04 p1, Point_test_08_04 p2);
};

class Point_test_08_04 {
private:
	double _ix = 0.0;
	double _iy = 0.0;

public:
	friend double Line_test_08_04::distance(Point_test_08_04 p1, Point_test_08_04 p2);

	Point_test_08_04() = default;

	Point_test_08_04(double ix, double iy): _ix(ix), _iy(iy) {
	}
};

double Line_test_08_04::distance(Point_test_08_04 p1, Point_test_08_04 p2) {
	const double x = p1._ix - p2._ix;
	const double y = p1._iy - p2._iy;
	return sqrt(x * x + y * y);
}

void test_08_04() {
	Point_test_08_04 p1(1.4, 3.3);
	Point_test_08_04 p2(4.4, 1.6);
	Line_test_08_04 l;
	std::cout << l.distance(p1, p2) << endl;
}

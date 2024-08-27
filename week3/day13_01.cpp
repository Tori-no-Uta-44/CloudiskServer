//
// Created by 李勃鋆 on 24-8-26.
//
#include <utility>

#include "../week03.h"

class Point13_01 {
public:
	explicit Point13_01(float x, float y):
		_x(x), _y(y) {
	}

	float _x = 0.0;
	float _y = 0.0;
};

class Line13_01 {
public:
	Line13_01(Point13_01 start, Point13_01 end):
		_startPoint(start), _endPoint(end) {
	}

	float distance() const {
		float dx = _endPoint._x - _startPoint._x;
		float dy = _endPoint._y - _startPoint._y;
		return sqrt(dx * dx + dy * dy);
	}

	Point13_01 _startPoint;
	Point13_01 _endPoint;
};

class Color13_01 {
public:
	Color13_01() = default;

	explicit Color13_01(string color):
		_color(std::move(color)) {

	}

	string _color;
};

class Triangle13_01 : public Line13_01, public Color13_01 {
public:
	Triangle13_01(Point13_01 start, Point13_01 end, string color, float height):
		Line13_01(start, end), Color13_01(std::move(color)), _height(height) {

	}

	double area() {
		return 0.5 * _height * distance();
	}

	float _height = 0.0;
};

void test13_01() {
	Point13_01 start(10, 6);
	Point13_01 end(10, 2);
	Triangle13_01 t(start, end, "red", 4.0);
	std::cout << t.area() <<" "<< t._color << endl;
}

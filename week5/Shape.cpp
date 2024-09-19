//
// Created by 李勃鋆 on 24-9-17.
//
#include "Shape.h"

namespace day30_1 {

	Rectangle::Rectangle(double width, double height):
		_width(width), _height(height) {
		cout << "Rectangle constructor" << endl;
	}

	void Rectangle::draw() {
		cout << "Drawing Rectangle" << endl;
	}

	double Rectangle::area() {
		return _width * _height;
	}

	Rectangle::~Rectangle() {
		cout << "Destroying Rectangle" << endl;
	}

	Circle::Circle(double radius):
		_radius(radius) {
		cout << "Circle constructor" << endl;
	}

	void Circle::draw() {
		cout << "Drawing Circle" << endl;
	}

	double Circle::area() {
		return 3.14 * _radius * _radius;
	}

	Circle::~Circle() {
		cout << "Destroying Circle" << endl;
	}

}

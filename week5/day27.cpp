//
// Created by 李勃鋆 on 24-9-11.
//
#include "../week5.h"

namespace day27 {
	class Shape {
	public:
		virtual void draw() =0;

		virtual double area() =0;

		virtual ~Shape() = default;
	};

	class Rectangle : public Shape {
		double _width = 0.0, _height = 0.0;

	public:
		Rectangle() = default;

		Rectangle(double width, double height):
			_width(width), _height(height) {
			cout << "Rectangle constructor" << endl;
		}

		void draw() override {
			cout << "Drawing Rectangle" << endl;
		}

		double area() override {
			return _width * _height;
		}

		~Rectangle() override {
			cout << "Destroying Rectangle" << endl;
		}
	};

	class Circle : public Shape {
		double _radius = 0.0;

	public:
		Circle() = default;

		explicit Circle(double radius):
			_radius(radius) {
			cout << "Circle constructor" << endl;
		}

		void draw() override {
			cout << "Drawing Circle" << endl;
		}

		double area() override {
			return 3.14 * _radius * _radius;
		}

		~Circle() override {
			cout << "Destroying Circle" << endl;
		}
	};

	class Square : public Shape {
		double _length = 0.0;

	public:
		Square() = default;

		explicit Square(double length):
			_length(length) {
			cout << "Square constructor" << endl;
		}

		void draw() override {
			cout << "Drawing Square" << endl;
		}

		double area() override {
			return _length * _length;
		}

		~Square() override {
			cout << "Destroying Square" << endl;
		}
	};

	class Factory {
	public:
		virtual Shape *createShape() =0;

		virtual ~Factory() = default;
	};

	class RectangleFactory : public Factory {
		Rectangle *_p = nullptr;

	public:
		Shape *createShape() override {
			_p = new Rectangle(1, 2);
			return _p;
		}

		~RectangleFactory() override {
			if (_p != nullptr) {
				delete _p;
				_p = nullptr;
			}
		}
	};

	class CircleFactory : public Factory {
		Circle *_p = nullptr;

	public:
		Shape *createShape() override {
			_p = new Circle(1);
			return _p;
		}

		~CircleFactory() override {
			if (_p != nullptr) {
				delete _p;
				_p = nullptr;
			}
		}
	};

	class SquareFactory : public Factory {
		Square *_p = nullptr;

	public:
		Square *createShape() override {
			_p = new Square(1);
			return _p;
		}

		~SquareFactory() override {
			if (_p != nullptr) {
				delete _p;
				_p = nullptr;
			}
		}
	};
}

void test27_1() {
	using namespace day27;
	auto *pr = new RectangleFactory();
	auto r = pr->createShape();
	r->draw();
	cout << r->area() << endl;
	auto *pc = new CircleFactory();
	auto c = pc->createShape();
	c->draw();
	cout << c->area() << endl;
	auto *ps = new SquareFactory();
	auto s = ps->createShape();
	s->draw();
	cout << s->area() << endl;

	delete ps;
	delete pc;
	delete pr;
}

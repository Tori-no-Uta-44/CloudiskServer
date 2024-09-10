//
// Created by 李勃鋆 on 24-9-9.
//
#include "../week5.h"

namespace day25 {
	class Figure {
	public:
		using DisplayCallback = function<void()>;
		using AreaCallback = function<double()>;

		void setDisplayCallback(DisplayCallback &&display) {
			_displayCallback = move(display);
			std::cout << "setDisplayCallback" << endl;
		}

		void setAreaCallback(AreaCallback &&area) {
			_areaCallback = move(area);
			std::cout << "setAreaCallback" << endl;
		}

		void handleDisplay() const {
			if (_displayCallback) {
				_displayCallback();
				cout << "displayCallback" << endl;
			}
		}

		[[nodiscard]] double handleArea() const {
			if (_areaCallback) {
				std::cout << "areaCallback" << endl;
				return _areaCallback();
			}
			return 0.0;
		}

	private:
		DisplayCallback _displayCallback;
		AreaCallback _areaCallback;
	};

	class Rectangle {
	public:
		Rectangle() = default;

		Rectangle(double width, double height):
			_width(width), _height(height) {
			std::cout << "Rectangle" << endl;
		}

		void display(int x) {
			std::cout << x << "\t" << "Rectangle display" << endl;
		}

		[[nodiscard]] double area() const {
			return _width * _height;
		}

		~Rectangle() {
			std::cout << "~Rectangle" << endl;
		}

	private:
		double _width = 0.0;
		double _height = 0.0;
	};

	class Circle {
	public:
		Circle() = default;

		explicit Circle(double radius):
			_radius(radius) {
			std::cout << "Circle" << endl;
		}

		void show() {
			cout << "show Circle" << endl;
		}

		[[nodiscard]] double area() const {
			return _radius * _radius * 3.14;
		}

		~Circle() {
			cout << "~Circle" << endl;
		}

	private:
		double _radius = 0.0;
	};

	class Triangle {
	public:
		Triangle() = default;

		Triangle(double a, double b, double c):
			_a(a), _b(b), _c(c) {
			std::cout << "Triangle" << endl;
		}

		void print() {
			std::cout << "Triangle print" << endl;
		}

		[[nodiscard]] double area() const {
			const double tmp = (_a + _b + _c) / 2.0;
			std::cout << "Triangle area = " << tmp << endl;
			return sqrt(tmp * (tmp - _a) * tmp * (tmp - _b) * tmp * (tmp - _c));
		}

		~Triangle() {
			std::cout << "~Triangle" << endl;
		}

	private:
		double _a = 0.0;
		double _b = 0.0;
		double _c = 0.0;
	};

	void func(const Figure &figure) {
		figure.handleDisplay();
		std::cout << figure.handleArea() << endl;
	}
}

void test25_1() {
	using namespace day25;
	Rectangle rectangle(3, 4);
	Circle circle(5);
	Triangle triangle(3, 4, 5);
	Figure figure;
	figure.setDisplayCallback([ObjectPtr = &rectangle] {
		ObjectPtr->display(42);
	});
	// figure.setAreaCallback(bind(&Rectangle::area, &rectangle));
	figure.setAreaCallback([ObjectPtr = &rectangle] {
		return ObjectPtr->area();
	});
	func(figure);

	figure.setDisplayCallback([ObjectPtr = &circle] {
		ObjectPtr->show();
	});
	// figure.setAreaCallback(bind(&Circle::area, &circle));
	figure.setAreaCallback([ObjectPtr = &circle] {
		return ObjectPtr->area();
	});
	func(figure);

	figure.setDisplayCallback([ObjectPtr = &triangle] {
		ObjectPtr->print();
	});
	// figure.setAreaCallback(bind(&Triangle::area, &triangle));
	figure.setAreaCallback([ObjectPtr = &triangle] {
		return ObjectPtr->area();
	});
	func(figure);
}

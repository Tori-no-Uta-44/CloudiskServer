//
// Created by 李勃鋆 on 24-9-12.
//
#include "../week5.h"

namespace day28_AFP {
	class AbstractShape {
	public:
		virtual ~AbstractShape() = default;

		virtual double area() =0;

		virtual void draw() =0;
	};

	class Rectangle : public AbstractShape {
		double _width = 0.0, _height = 0.0;

	public:
		Rectangle() = default;

		explicit Rectangle(double width, double height):
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

	class Circle : public AbstractShape {
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

	class Square : public AbstractShape {
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

	class AbstractColor {
	public:
		virtual ~AbstractColor() = default;

		virtual void fill() =0;
	};

	class Red : public AbstractColor {
	public:
		void fill() override {
			cout << "Red fill" << endl;
		}
	};

	class Green : public AbstractColor {
	public:
		void fill() override {
			cout << "Green fill" << endl;
		}
	};

	class Blue : public AbstractColor {
	public:
		void fill() override {
			cout << "Blue fill" << endl;
		}
	};

	class AbstractFactory {
	public:
		virtual ~AbstractFactory() = default;

		virtual AbstractShape *getShape() =0;

		virtual AbstractColor *getColor() =0;
	};

	class RectangleFactory : public AbstractFactory {
		Rectangle *getShape() override {
			return new Rectangle(1, 2);
		}

		Red *getColor() override {
			return new Red();
		}

	};

	class CircleFactory : public AbstractFactory {
		Circle *getShape() override {
			return new Circle(3);
		}

		Green *getColor() override {
			return new Green();
		}
	};

	class SquareFactory : public AbstractFactory {
		Square *getShape() override {
			return new Square(4);
		}

		Blue *getColor() override {
			return new Blue();
		}
	};

	class Observer {
	public:
		virtual ~Observer() = default;

		virtual void update(int status) =0;
	};

	class Subject {
	public:
		virtual void attach(Observer *po) =0;

		virtual void detach(Observer *po) =0;

		virtual void notify() =0;

		virtual ~Subject() = default;
	};

	class ConcreteSubject : public Subject {
		list<Observer *> _obList;
		int _status = 0;

	public:
		void attach(Observer *po) override {
			_obList.push_back(po);
		}

		void detach(Observer *po) override {
			_obList.remove(po);
		}

		void notify() override {
			for (auto &i : _obList) {
				i->update(_status);
			}
		}

		void set_status(int status) {
			_status = status;
			notify();
		}
	};

	class BinaryObserver : public Observer {
	public:
		void update(int status) override {
			cout << "Updating BinaryObserver " << status << endl;
		}
	};
	class OctalObserver : public Observer {
	public:
		void update(int status) override {
			cout << "Updating OctalObserver " << status << endl;
		}
	};
}

void test28_1() {
	using namespace day28_AFP;
	unique_ptr<AbstractFactory> factory1(new RectangleFactory);
	unique_ptr<AbstractFactory> factory2(new CircleFactory);
	unique_ptr<AbstractFactory> factory3(new SquareFactory);
	auto *pr = factory1->getShape();
	pr->draw();
	cout << pr->area() << endl;
	auto *pc = factory1->getColor();
	pc->fill();
	delete pr;
	delete pc;
	auto *pr2 = factory2->getShape();
	pr2->draw();
	cout << pr2->area() << endl;
	auto *pc2 = factory2->getColor();
	pc2->fill();
	delete pr2;
	delete pc2;
	auto *pr3 = factory3->getShape();
	pr3->draw();
	cout << pr3->area() << endl;
	auto *pc3 = factory3->getColor();
	pc3->fill();
	delete pr3;
	delete pc3;
}

void test28_2() {
	using namespace day28_AFP;
	auto *pc=new ConcreteSubject();
	Observer *pb = new BinaryObserver();
	Observer *po = new OctalObserver();
	pc->attach(pb);
	pc->set_status(1);
	pc->attach(po);
	pc->notify();
	pc->detach(po);
	pc->set_status(2);
	pc->notify();
	delete po;
	delete pb;
	delete pc;
}
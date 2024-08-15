//
// Created by 李勃鋆 on 24-8-16.
//

#include "../week01.h"

class S {
public:
	S() {
		i = 0;
		k++;
	}
	
	void toString() const {
		std::cout << i << "--" << k << std::endl;
	}

private:
	int i;
	static int k;
};

int S::k = 0;

void test_05_01() {
	S a = S();
	a.toString();
	S b = S();
	b.toString();
}

int i = 1;

class T {
public:
	T() : fourth(third), second(i++), first(i++), third(i++) {
		third = i;
	}
	
	void toString() const {
		std::cout << first << " " << second << " " << third << " " << fourth << std::endl;
		std::cout << first + second + third + fourth << std::endl;
	}

private:
	int first;
	int second;
	int third;
	int &fourth;
};

void test_05_02() {
	T a = T();
	a.toString();
}

class P {
private:
	double x;
	double y;
public:
	P(int x = 0, int y = 0) : x(x), y(y) {
		std::cout << "pc" << std::endl;
	}
	
	P(const P &p) : x(p.x), y(p.y) {
		std::cout << "pco" << std::endl;
	}
	
	double getX() const {
		return x;
	}
	
	double getY() const {
		return y;
	}
};

class D {
private:
	P p1;
	P p2;
	double dist;
public:
	D(const P &p1, const P &p2) : p1(p1), p2(p2) {
		std::cout << "dc" << std::endl;
		double x = p1.getX() - p2.getX();
		double y = p1.getY() - p2.getY();
		std::cout << p1.getX() << " " << p1.getY() << std::endl;
		std::cout << p2.getX() << " " << p2.getY() << std::endl;
		std::cout << x << " " << y << std::endl;
		dist = sqrt(x * x + y * y);
	}
	
	void toString() const {
		std::cout << dist << std::endl;
	}
};

void test_05_03() {
	P p1 = P(1, 1);
	P p2 = P(4, 5);
	D d = D(p1, p2);
	d.toString();
}

class M {
public:
	M(int = 0) {
		std::cout << i;
	}
	
	M(const M &m) {
		std::cout << 2.0;
	}
	
	M &operator=(const M &m) {
		std::cout << 3;
		return *this;
	}
	
	~M() {
		std::cout << 4;
	}
};

void test_05_04() {
	M m1 = M(1);
	M m2 = M(2);
	M m3 = m1;
	m3 = 5;
}

class Point {
private:
	int ix;
	int iy;
	static Point *p;
	
	Point() = default;
	
	Point(int x, int y) : ix(x), iy(y) {
		std::cout << "(int,int)" << std::endl;
	}
	
	~Point() {
		std::cout << "~Point()" << std::endl;
	}

public:
	Point(const Point &p) = delete;
	
	Point &operator=(const Point &p) = delete;
	
	static Point *createPoint() {
		if (p == nullptr) {
			p = new Point(0, 0);
			std::cout << "createPoint()" << std::endl;
		}
		return p;
	}
	
	void set(int x, int y) {
		ix = x;
		iy = y;
	}
	
	void toString() const {
		std::cout << ix << "," << iy << std::endl;
	}
	
	static void destroy() {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
		std::cout << "destroy()" << std::endl;
	}
};

Point *Point::p = nullptr;

void test_05_05() {
	Point::createPoint()->set(5, 6);
	Point::createPoint()->toString();
	Point::destroy();
}

class Computer {
private:
	char *_brand;
	double _price;
	static Computer *pc;
	
	Computer() = default;
	
	Computer(const char *brand, double price) : _brand(new char[std::strlen(brand) + 1]()), _price(price) {
		std::strcpy(this->_brand, brand);
		std::cout << "(char*,double)" << std::endl;
	}
	
	~Computer() {
		if (_brand != nullptr) {
			delete[]_brand;
			_brand = nullptr;
		}
	}

public:
	Computer(const Computer &c) = delete;
	
	Computer &operator=(const Computer &c) = delete;
	
	static Computer *computerInstance() {
		if (pc == nullptr) {
			pc = new Computer("", 0);
		}
		return pc;
	}
	
	void set(char *brand, double price) {
		delete[] this->_brand;
		this->_brand = new char[std::strlen(brand) + 1]();
		std::strcpy(this->_brand, brand);
		this->_price = price;
	}
	
	void toString() {
		std::cout << _brand << "," << _price << std::endl;
	}
	
	static void destroy() {
		if (pc != nullptr) {
			delete pc;
			pc = nullptr;
		}
	}
};

Computer *Computer::pc = nullptr;

void test_05_06() {
	Computer::computerInstance()->set("HP", 5000);
	Computer::computerInstance()->toString();
	Computer::destroy();
}
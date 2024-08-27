//
// Created by 李勃鋆 on 24-8-27.
//
#include "../week03.h"

class A_14_01 {
public:
	virtual ~A_14_01() = default;

	virtual void print() {
		cout << "A_14_01_print" << endl;
	}

	virtual void display() {
		cout << "A_14_01_display" << endl;
	}

	virtual void show() {
		cout << "A_14_01_show" << endl;
	}

private:
	long _a = 1;
};

class B_14_01 : public A_14_01 {
public:
	void print() override {
		cout << "B_14_01_print" << endl;
	}
	void display() override {
		cout << "B_14_01_display" << endl;
	}
	void show() override {
		cout << "B_14_01_show" << endl;
	}
private:
	long _b=10;
};

void test_14_01() {
	B_14_01 b;
	long * pb=reinterpret_cast<long *>(&b);
	std::cout << pb[0] << std::endl;
	std::cout << pb[1] << std::endl;
	std::cout << pb[2] << std::endl;
	std::cout << "---"<< std::endl;
	long * pa=reinterpret_cast<long *>(pb[0]);
	cout << pa[0] << endl;
	cout << pa[1] << endl;
	cout << pa[2] << endl;
	std::cout << "---"<< std::endl;
	typedef void (*fun_ptr)();
	auto f=reinterpret_cast<fun_ptr>(pa[0]);
	f();
	f=reinterpret_cast<fun_ptr>(pa[1]);
	f();
	f=reinterpret_cast<fun_ptr>(pa[2]);
	f();
}

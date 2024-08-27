//
// Created by 李勃鋆 on 24-8-27.
//
#include "../week03.h"
class A_14_02 {
public:
	virtual ~A_14_02() = default;

	A_14_02(){
		cout<<"A_14_02Constructor"<<endl;
	}
	virtual void a() {
		cout<<"A_14_02_a"<<endl;
	}
	virtual void b() {
		cout<<"A_14_02_b"<<endl;
	}
	virtual void c() {
		cout<<"A_14_02_c"<<endl;
	}
private:
	double _a=1.0;
};
class B_14_02 {
public:
	virtual ~B_14_02() = default;

	B_14_02(){
		cout<<"B_14_02Constructor"<<endl;
	}
	virtual void a() {
		cout<<"B_14_02_a"<<endl;
	}
	virtual void b() {
		cout<<"B_14_02_b"<<endl;
	}
	virtual void c() {
		cout<<"B_14_02_c"<<endl;
	}
private:
	double _b=2.0;
};
class C_14_02 {
public:
	virtual ~C_14_02() = default;

	C_14_02(){
		cout<<"C_14_02Constructor"<<endl;
	}
	virtual void a() {
		cout<<"C_14_02_a"<<endl;
	}
	virtual void b() {
		cout<<"C_14_02_b"<<endl;
	}
	virtual void c() {
		cout<<"C_14_02_c"<<endl;
	}
private:
	double _c=3.0;
};
class D_14_02:public A_14_02,public B_14_02,public C_14_02 {
public:
	D_14_02() {
		cout<<"D_14_02Constructor"<<endl;
	}
	void a() override {
		cout<<"D_14_02_a"<<endl;
	}
	virtual void d() {
		cout<<"D_14_02_d"<<endl;
	}
private:
	double _d=4.0;
};

void test14_02() {
	std::cout << sizeof(D_14_02)<<endl;
	D_14_02 d;
	A_14_02 *a=&d;
	B_14_02 *b=&d;
	C_14_02 *c=&d;

	std::cout << &d<<std::endl;
	std::cout << a<<std::endl;
	std::cout << b<<std::endl;
	std::cout << c<<std::endl;
}
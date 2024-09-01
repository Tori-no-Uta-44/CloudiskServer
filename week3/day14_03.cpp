//
// Created by 李勃鋆 on 24-8-27.
//
#include "../week03.h"

class A {
public:
	virtual ~A() = default;

	virtual void a() { cout << "A::a()" << endl; }
	virtual void b() { cout << "A::b()" << endl; }
	virtual void c() { cout << "A::c()" << endl; }

};

class B {
public:
	virtual ~B() = default;

	virtual void a() { cout << "B::a()" << endl; }
	virtual void b() { cout << "B::b()" << endl; }
	virtual void c() { cout << "B::c()" << endl; }
	void d() { cout << "B::d()" << endl; }
};

class C
	: public A
	  , public B {
public:
	void a() override { cout << "C::a()" << endl; }
	void c() override { cout << "C::c()" << endl; }
	void d() { cout << "C::d()" << endl; }
};


//先不看D类
class D
	: public C {
public:
	void c() override { cout << "D::c()" << endl; }
};

void test14_03() {
	C c;
	c.a();
	// c.b();
	c.c();
	c.d();

	cout << endl;
	A *pa = &c;
	pa->a();
	pa->b();
	pa->c();
	// pa->d();

	cout << endl;
	B *pb = &c;
	pb->a();//C::a()
	pb->b();//B::b()
	pb->c();//B::c()
	pb->d();//C::d()


	cout << endl;
	C *pc = &c;
	pc->a();//C::a()
	// pc->b();//函数调用不明确。 可行候选项: virtual void b() (class A 中) virtual void b() (class B 中)
	pc->c();//C::c()
	pc->d();//C::d()
}

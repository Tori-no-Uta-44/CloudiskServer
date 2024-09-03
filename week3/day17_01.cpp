//
// Created by 李勃鋆 on 24-8-30.
//
#include "../week03.h"

void test17_01() {
	int a = 10;
	std::cout << &a << std::endl;
	int &&ref = move(a);
	std::cout << &ref << std::endl;
	ref = 100;
	std::cout << a << std::endl;
}

int a_17_1 = 21;

int func17_1() {
	return a_17_1;
}

int &func17_1_ref() {
	return a_17_1;
}

int &&func_17_1_move() {
	return move(a_17_1);
}

// int &&func17_1_move2() {
// 	int a = 1, b = 2;
// 	return a + b;
// }

void test17_2() {
	cout << &func17_1_ref() << endl;
	cout << &a_17_1 << endl;
	int &&ref = func_17_1_move();
	cout << &ref << endl;
	// int &&x = func17_1_move2();
	// cout << &x << endl;
	// x = 0;
}

// 前向声明
template <typename T>
class RAII;

// Computer17_1 类
class Computer17_1 {
private:
	std::string *_brand;
	double _price;
	static Computer17_1 *pc;

	Computer17_1() = default;

	Computer17_1(const std::string &brand, double price)
		: _brand(new std::string(brand)), _price(price) {}

	~Computer17_1() {
		if (_brand != nullptr) {
			delete _brand;
			_brand = nullptr;
		}
		std::cout << "Computer17_1 destroyed." << std::endl;
	}

public:
	Computer17_1(const Computer17_1 &c) = delete;
	Computer17_1 &operator=(const Computer17_1 &c) = delete;

	static Computer17_1* computerInstance() {
		if (pc == nullptr) {
			pc = new Computer17_1("", 0);
		}
		return pc;
	}

	void set(std::string brand, double price) {
		*_brand = std::move(brand);
		this->_price = price;
	}

	void toString() const {
		std::cout << *_brand << ", " << _price << std::endl;
	}

	static void destroy() {
		if (pc != nullptr) {
			delete pc;
			pc = nullptr;
		}
	}

	// 将 RAII 类声明为友元类
	template <typename T>
	friend class RAII;
};

Computer17_1* Computer17_1::pc = nullptr;

// RAII 模板类
template <typename T>
class RAII {
private:
	T* _resource;

public:
	// 构造函数：传入已有的资源指针
	RAII(T* resource) : _resource(resource) {}

	// 析构函数：释放资源
	~RAII() {
		if (_resource) {
			delete _resource;
			_resource = nullptr;
		}
	}

	// 禁用拷贝构造函数和赋值运算符
	RAII(const RAII&) = delete;
	RAII& operator=(const RAII&) = delete;

	// 提供对资源的访问
	T* operator->() {
		return _resource;
	}

	const T* operator->() const {
		return _resource;
	}

	// 提供对资源的引用
	T& operator*() {
		return *_resource;
	}

	const T& operator*() const {
		return *_resource;
	}
};

void test17_3() {
	RAII<Computer17_1> computer(Computer17_1::computerInstance());
	computer->set("HP", 5000);
	computer->toString();
}

// void test17_4() {
// 	int *p = new int(11);
// 	auto_ptr<int> a(p);
// 	cout << p << endl;
// 	cout << a.get() << endl;
// 	cout << *a << endl;
// 	auto_ptr<int> b = a;
// 	cout << b.get() << endl;
// 	cout << *b << endl;
// 	cout << *a << endl;
// }

void test17_5() {
	unique_ptr<int> p(new int(22));
	cout << *p << endl;
	cout << p.get() << endl;
	unique_ptr<int> p2(new int(33));
	unique_ptr<int> p3((std::move(p2)));
	cout << *p2 << endl;
	cout << *p3 << endl;
	cout << "---" << endl;
	shared_ptr<int> sp(new int(44));
	shared_ptr<int> sp2(sp);
	cout << *sp << endl;
	cout << *sp2 << endl;
	cout << sp.get() << endl;
	cout << sp.use_count() << endl;
	cout << sp2.use_count() << endl;
}

class Child17_01;

class Parent17_01 {
public:
	shared_ptr<Child17_01> _child;
};

class Child17_01 {
public:
	shared_ptr<Parent17_01> _parent;
};

void test17_6() {
	shared_ptr<Parent17_01> p(new Parent17_01);
	shared_ptr<Child17_01> c(new Child17_01);
	cout << p->_child.use_count() << endl;
	cout << c.use_count() << endl;
	std::cout << "---" << endl;
	p->_child = c;
	c->_parent = p;
	cout << p.use_count() << endl;
	cout << p.use_count() << endl;
}

class Child17_02;

class Parent17_02 {
public:
	~Parent17_02() {
		cout<<"Parent17_02::~Parent17_02"<<endl;
	}
	shared_ptr<Child17_02> _child;
};

class Child17_02 {
public:
	~Child17_02() {
		cout << "Child17_02::~Child17_02" << endl;
	}

	weak_ptr<Parent17_02> _parent;
};

void test17_7() {
	shared_ptr<Parent17_02> p(new Parent17_02);
	weak_ptr<int> wp;
	shared_ptr<Child17_02> c(new Child17_02);
	cout << p->_child.use_count() << endl;
	cout << c.use_count() << endl;
	std::cout << "---" << endl;
	p->_child = c;
	c->_parent = p;
	cout << p.use_count() << endl;
	cout << p.use_count() << endl;
}

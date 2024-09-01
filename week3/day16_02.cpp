//
// Created by 李勃鋆 on 24-8-29.
//
#include "../week03.h"

class MyString_16_05 {
private:
	char *_pstr;

public:
	MyString_16_05():
		_pstr(new char[1]()) {
	}

	explicit MyString_16_05(const char *pstr):
		_pstr(new char[strlen(pstr) + 1]()) {
		std::cout << "MyString_16_05::MyString_16_05()" << std::endl;
		strcpy(_pstr, pstr);
	}

	MyString_16_05(const MyString_16_05 &rhs):
		_pstr(new char[strlen(rhs.c_str()) + 1]()) {
		std::cout << "copy constructor" << std::endl;
		strcpy(_pstr, rhs.c_str());
	}


	MyString_16_05 &operator=(const MyString_16_05 &rhs) {
		std::cout << "copy assignment operator" << std::endl;
		if (this != &rhs) {
			delete[] _pstr;
			_pstr = new char[strlen(rhs.c_str()) + 1]();
			strcpy(_pstr, rhs.c_str());
		}
		return *this;
	}

	MyString_16_05(MyString_16_05 &&rhs)  noexcept :_pstr(rhs._pstr) {
		std::cout << "move constructor" << std::endl;
		rhs._pstr = nullptr;
	}
	MyString_16_05 & operator=(MyString_16_05 &&rhs)  noexcept {
		std::cout << "move assignment operator" << std::endl;
		if (this != &rhs) {
			delete[] _pstr;
			_pstr=rhs._pstr;
			rhs._pstr=nullptr;
		}
		return *this;
	}

	~MyString_16_05() {
		delete[] _pstr;
		_pstr = nullptr;
	}

	void toString() const {
		std::cout << _pstr << std::endl;
	}

	[[nodiscard]] size_t length() const {
		return strlen(_pstr);
	}

	[[nodiscard]] const char *c_str() const {
		return _pstr;
	}

};

void test16_05() {
	MyString_16_05 str1("aa");
	str1.toString();
	MyString_16_05 str2("hello");
	MyString_16_05 str3("Hello, World!");
	str2.toString();
	str3.toString();
	MyString_16_05 str4 = str3;
	str4.toString();
	str1 = str2;
	str1.toString();
	MyString_16_05 str5 = std::move(MyString_16_05("fuck"));
	str1=std::move(MyString_16_05("fuck"));
	MyString_16_05 s6("hello");
	s6 = MyString_16_05("wangdao");
}

//
// Created by 李勃鋆 on 24-8-21.
//
#include <utility>

#include "../week02.h"

class Base_test_09_01 {
private:
	int _data;

public:
	explicit Base_test_09_01(int data): _data(data) {
	}

	Base_test_09_01 operator+(const Base_test_09_01& p) const {
		return Base_test_09_01(p._data - this->_data);
	}

	friend bool operator==(const Base_test_09_01& p1, int data);
};

bool operator==(const Base_test_09_01& p1, const int data) {
	return p1._data == data;
}

void test_09_01() {
	int i = 2;
	int j = 7;
	Base_test_09_01 x(i);
	Base_test_09_01 y(j);
	cout << (x + y == j - i) << endl;
}

class Complex_test_09_02 {
public:
	Complex_test_09_02() = default;

	Complex_test_09_02(int data, string name, double tmp): _data(data), _name(std::move(name)), _tmp(tmp) {
	}

	Complex_test_09_02 operator+(const Complex_test_09_02& p1) const {
		Complex_test_09_02 t;
		t._data = this->_data + p1._data;
		t._name = this->_name + "+" + p1._name + "|";
		t._tmp = this->_tmp + p1._tmp;
		return t;
	}

	Complex_test_09_02 operator-(const Complex_test_09_02& p1) const {
		Complex_test_09_02 t;
		t._data = this->_data - p1._data;
		t._name = this->_name + "-" + p1._name + "|";
		t._tmp = this->_tmp - p1._tmp;
		return t;
	}

	Complex_test_09_02& operator-=(const Complex_test_09_02& p1) {
		this->_data -= p1._data;
		this->_name + "-= |";
		this->_tmp -= p1._tmp;
		return *this;
	}

	Complex_test_09_02& operator+=(const Complex_test_09_02& p1) {
		this->_data += p1._data;
		this->_name + "+= |";
		this->_tmp += p1._tmp;
		return *this;
	}

	Complex_test_09_02& operator++() {
		this->_data++;
		this->_name += "++ |";
		this->_tmp++;
		return *this;
	}

	Complex_test_09_02& operator--(int) {
		this->_data--;
		this->_name += "-- |";
		this->_tmp--;
		return *this;
	}

	// void operator<<(Complex_test_09_02 &p) {
	// 	std::cout << p._data << "\t" << p._name << "\t" << p._tmp << endl;
	// }

	friend ostream& operator<<(ostream& out, const Complex_test_09_02& p);

	friend istream& operator>>(istream& in, Complex_test_09_02& p);
	void toString() const {
		std::cout << _data << "\t" << _name << "\t" << _tmp << endl;
	}

private:
	int _data = 0;
	string _name;
	double _tmp = 0.0;
};

ostream& operator<<(ostream& out, const Complex_test_09_02& p) {
	out << "_data" << p._data << "\t" << p._name << "\t" << p._tmp;
	return out;
}

istream& operator>>(istream& in, Complex_test_09_02& p) {
	in>>p._name;
	in>>p._data;
	in>>p._tmp;
	return in;
}

void test_demo_09_02() {
	Complex_test_09_02 x(1, "x_02", 1.5);
	Complex_test_09_02 y(22, "y_02", 22.55);
	++x;
	x.toString();
	// x.operator<<(y);
	// x<<y;
	operator<<(cout,y)<<endl;
	cout << x << endl;
}

const int SIZE = 10;

class Safearay {
public:
	int& operator[](int index) {
		if (index >= SIZE) {
			throw std::out_of_range("index out of range");
		}
		return arr[index];
	}

private:
	int arr[SIZE] = {0};
};

void demo_09_01() {
	Safearay a;
	try {
		cout << a[2] << endl;
		cout << a[15] << endl;
	}
	catch (std::out_of_range& e) {
		cout << e.what() << endl;
	}
}

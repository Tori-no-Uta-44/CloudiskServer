//
// Created by 李勃鋆 on 24-8-23.
//
#include "../week02.h"
// 写时复制区分取值与修改，使用代理模式
// 创建一个CowString类的内部类，让CowString的operator[]函数返回是这个新类型的对象，
// 然后在这个新类型中对<<和=进行重载，让这两个运算符能够处理新类型对象，从而分开了处理逻辑。

class CowString_test_11_07 {
public:
	// 内部代理类 My_class
	class My_class {
	public:
		My_class(CowString_test_11_07 &str, size_t index) :
			_str(str), _index(index) {
		}

		// 重载赋值运算符，用于修改操作
		My_class &operator=(const char ch) {
			if (_index < _str.size()) {
				if (_str.use_count() > 1) {
					_str.decrease();
					char *temp = _str.create(_str._pstr);
					strcpy(temp, _str._pstr);
					_str._pstr = temp;
					_str.init();
				}
				_str._pstr[_index] = ch;
			}
			return *this;
		}

		// 重载赋值运算符，用于代理对象赋值
		My_class &operator=(const My_class &rhs) {
			return *this = static_cast<char>(rhs);
		}

		// 类型转换运算符，用于取值操作
		explicit operator char() const {
			return _str._pstr[_index];
		}

	private:
		CowString_test_11_07 &_str;
		size_t _index;
	};

	// CowString 类的公开接口
	CowString_test_11_07();

	explicit CowString_test_11_07(const char *pstr);

	CowString_test_11_07(const CowString_test_11_07 &rhs);

	CowString_test_11_07 &operator=(const CowString_test_11_07 &rhs);

	~CowString_test_11_07();

	size_t size() const {
		return strlen(_pstr);
	}

	const char *c_str() const {
		return _pstr;
	}

	int use_count() const {
		return *reinterpret_cast<int *>(_pstr - length);
	}

	My_class operator[](size_t index) {
		return {*this, index};
	}

	friend ostream &operator<<(ostream &out, const CowString_test_11_07 &rhs);

	friend ostream &operator<<(ostream &out, const My_class &proxy);

private:
	static const int length = 4;
	char *_pstr;

	void init() {
		*reinterpret_cast<int *>(_pstr - length) = 1;
	}

	void increase() {
		++*reinterpret_cast<int *>(_pstr - length);
	}

	void decrease() {
		--*reinterpret_cast<int *>(_pstr - length);
	}

	char *create(const char *pstr = nullptr) {
		if (pstr) {
			return new char[strlen(pstr) + 1 + length]() + length;
		}
		return new char[1 + length]() + length;
	}

	void release() {
		decrease();
		if (use_count() == 0) {
			delete[] (_pstr - length);
		}
		_pstr = nullptr;
	}
};

CowString_test_11_07::CowString_test_11_07() :
	_pstr(create()) {
	init();
}

CowString_test_11_07::CowString_test_11_07(const char *pstr) :
	_pstr(create(pstr)) {
	strcpy(_pstr, pstr);
	init();
}

CowString_test_11_07::CowString_test_11_07(const CowString_test_11_07 &rhs) :
	_pstr(rhs._pstr) {
	increase();
}

CowString_test_11_07 &CowString_test_11_07::operator=(const CowString_test_11_07 &rhs) {
	if (this != &rhs) {
		release();
		_pstr = rhs._pstr;
		increase();
	}
	return *this;
}

CowString_test_11_07::~CowString_test_11_07() {
	release();
}

ostream &operator<<(ostream &out, const CowString_test_11_07 &rhs) {
	out << rhs._pstr;
	return out;
}

 ostream &operator<<(ostream &out, const CowString_test_11_07::My_class &proxy){
	out << static_cast<char>(proxy);
	return out;
}

void test_11_07() {
	CowString_test_11_07 str1("world");
	CowString_test_11_07 str2 = str1;
	cout << str1[0] << endl;
	str1[0] = 'W';
	cout << str1 << endl;
	cout << str2 << endl;
	cout << "str1.use_count: " << str1.use_count() << endl;
	cout << "str2.use_count: " << str2.use_count() << endl;
}

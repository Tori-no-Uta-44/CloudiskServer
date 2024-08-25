//
// Created by 李勃鋆 on 24-8-25.
//
#include "../week02.h"

class String_12_03 {
public:
	String_12_03(const char *pstr);

	~String_12_03();

	char &operator[](size_t idx);

	friend
	ostream &operator<<(ostream &os, const String_12_03 &rhs);

private:
	union Buffer {
		char *_pointer;
		char _local[16];
	};

	size_t _size;
	size_t _capacity;
	Buffer _buffer;
};

String_12_03::String_12_03(const char *pstr):
	_size(strlen(pstr) + 1), _capacity(_size) {
	if (_size > 16) {
		printf("%p\n", _buffer._pointer);
		printf("%p\n", _buffer._local);
		_buffer._pointer = new char[_size];
		strcpy(_buffer._pointer, pstr);
		std::cout << "Heap: " << _buffer._pointer << std::endl;
		printf("%p\n", _buffer._pointer);
		printf("%p\n", _buffer._local);
	}
	else {
		printf("%p\n", _buffer._pointer);
		printf("%p\n", _buffer._local);
		strcpy(_buffer._local, pstr);
		std::cout << "Local: " << _buffer._local << std::endl;
		printf("%p\n", _buffer._pointer);
		printf("%p\n", _buffer._local);
	}
}

String_12_03::~String_12_03() {
	if (_size > 16) {
		delete[] _buffer._pointer;
		_buffer._pointer = nullptr;
	}
}

char &String_12_03::operator[](size_t idx) {
	if (_size > 16) {
		return _buffer._pointer[idx];
	}
	return _buffer._local[idx];

}

ostream &operator<<(ostream &os, const String_12_03 &rhs) {
	if (rhs._size > 16) {
		os << rhs._buffer._pointer << endl;
	}
	os << rhs._buffer._local << endl;
	return os;
}

void test_12_03() {
	String_12_03 str1("hello");
	String_12_03 str2("hello,world!!!!!");
	//...
}

//
// Created by 李勃鋆 on 24-8-23.
//
#include "../week02.h"

class String_test_11_06 {
	union Buffer {
		char* _pointer;
		char _local[16];
	};

	size_t _size;
	size_t _capacity;
	Buffer _buffer;
	bool _isHeapAllocated;

public:
	String_test_11_06(const char* data)
		: _size(strlen(data) + 1),
		  _capacity(_size),
		  _isHeapAllocated(_size > 16) {
		if (_isHeapAllocated) {
			_buffer._pointer = new char[_size];
			strcpy(_buffer._pointer, data);
			std::cout << "Heap: " << _buffer._pointer << std::endl;
		} else {
			strcpy(_buffer._local, data);
			std::cout << "Local: " << _buffer._local << std::endl;
		}
	}

	~String_test_11_06() {
		if (_isHeapAllocated) {
			delete[] _buffer._pointer;
			_buffer._pointer = nullptr;
		}
	}
};

void test_11_06() {
	char str[] = "Hello,World!abcdefghijk";
	String_test_11_06 test01(str);

	std::cout << "---" << std::endl;

	char str2[] = "Hello,World!";
	String_test_11_06 test02(str2);
}
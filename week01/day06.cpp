//
// Created by 李勃鋆 on 24-8-17.
//
#include "../week01.h"

class Points {
private:
	int _ix;
	int _iy;

public:
	Points(): _ix(0), _iy(0) {
	}

	explicit Points(int ix, int iy = 0): _ix(ix), _iy(iy) {
	}

	void toString() const {
		std::cout << "(" << _ix << "," << _iy << ")" << std::endl;
	}
};

void test_06_01() {
	Points p1 = Points(1, 2);
	Points p2 = Points(3, 4);
	std::vector<Points> points;
	points.push_back(p1);
	points.push_back(p2);
	for (auto point : points) {
		point.toString();
	}
}

void test_06_02() {
	std::vector<int> data = {0, 1};
	std::vector<std::vector<int>> num = {{2, 3}};
	num.push_back(data);
	for (auto& i : num) {
		for (int j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}

class MyString {
private:
	char* _pstr;

public:
	MyString();
	explicit MyString(const char* pstr);
	MyString(const MyString& rhs);
	MyString& operator=(const MyString& rhs);
	~MyString();
	void toString() const;
	size_t length() const;
	[[nodiscard]] const char* c_str() const;
};

MyString::MyString(): _pstr(new char[1]()) {
}

MyString::MyString(const char* pstr): _pstr(new char[strlen(pstr) + 1]()) {
	strcpy(_pstr, pstr);
}

MyString::MyString(const MyString& rhs): _pstr(new char[strlen(rhs.c_str()) + 1]()) {
	strcpy(_pstr, rhs.c_str());
}

MyString& MyString::operator=(const MyString& rhs) {
	if (this != &rhs) {
		delete _pstr;
		_pstr = new char[strlen(rhs.c_str()) + 1]();
		strcpy(_pstr, rhs.c_str());
	}
	return *this;
}

MyString::~MyString() {
	delete[] _pstr;
	_pstr = nullptr;
}

void MyString::toString() const {
	std::cout << _pstr << std::endl;
}

size_t MyString::length() const {
	return strlen(_pstr);
}

const char* MyString::c_str() const {
	const size_t len = strlen(_pstr);
	char buffer[len + 1];
	strcpy(buffer, _pstr);
	buffer[len] = '\0';
	char* p = buffer;
	return p;
}

void test_06_03() {
	MyString str1 = MyString();
	str1.toString();
	MyString str2 = MyString("hello");
	MyString str3 = MyString("Hello, World!");
	str2.toString();
	str3.toString();
	MyString str4 = str3;
	str4.toString();
	str4 = str2;
	str4.toString();
}

class StackNode {
public:
	int val;
	StackNode* next;
};

class Stack {
public:
	bool empty();
	bool full();
	void push(int data);
	void pop();
	int top();

	StackNode* stack_node;
	int size;
	int capacity;

	Stack(int cap = 16) : stack_node(nullptr), size(0), capacity(cap) {
	}

	~Stack();
};

bool Stack::empty() {
	return size == 0;
}

bool Stack::full() {
	return size == capacity;
}

void Stack::push(int data) {
	if (full()) {
		std::cout << "Stack is Full" << std::endl;
		return;
	}
	StackNode* newNode = new StackNode;
	newNode->val = data;
	newNode->next = stack_node;
	stack_node = newNode;
	size++;
}

void Stack::pop() {
	if (empty()) {
		std::cout << "Stack is empty!" << std::endl;
		return;
	}
	StackNode* temp = stack_node;
	stack_node = stack_node->next;
	delete temp;
	size--;
}

int Stack::top() {
	if (empty()) {
		std::cout << "Stack is empty!" << std::endl;
		return -1;
	}
	return stack_node->val;
}

Stack::~Stack() {
	while (stack_node != nullptr) {
		StackNode* temp = stack_node;
		stack_node = stack_node->next;
		delete temp;
	}
}

void test_06_04() {
	Stack s(5);
	s.push(10);
	s.push(20);
	s.push(30);

	while (!s.empty()) {
		std::cout << "Top: " << s.top() << std::endl;
		s.pop();
	}
}

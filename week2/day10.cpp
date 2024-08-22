//
// Created by 李勃鋆 on 24-8-22.
//
#include "../week02.h"

class String {
public:
	String();

	explicit String(const char* pstr);

	String(const String& pstr);

	~String();

	String& operator=(const String& pstr);

	String& operator=(const char* pstr);

	String& operator+=(const String& pstr);

	String& operator+=(const char* pstr);

	char& operator[](std::size_t index);

	const char& operator[](std::size_t index) const;

	std::size_t size() const;

	const char* c_str() const;

	friend bool operator==(const String& data1, const String& data2);

	friend bool operator!=(const String& data1, const String& data2);

	friend bool operator<(const String& data1, const String& data2);

	friend bool operator>(const String& data1, const String& data2);

	friend bool operator<=(const String& data1, const String& data2);

	friend bool operator>=(const String& data1, const String& data2);

	friend std::ostream& operator<<(std::ostream& os, const String& s);

	friend std::istream& operator>>(std::istream& is, String& s);

private:
	char* _pstr;
};

String operator+(const String&, const String&);

String operator+(const String&, const char*);

String operator+(const char*, const String&);

String::String(): _pstr(new char[1]()) {
}

String::~String() {
	if (_pstr != nullptr) {
		delete[] _pstr;
		_pstr = nullptr;
	}
}

std::ostream& operator<<(std::ostream& os, const String& s) {
	os << s._pstr;
	return os;
}

const char* String::c_str() const {
	if (_pstr == nullptr) {
		static char nullChar = '\0';
		return &nullChar;
	}
	return _pstr;
}

String::String(const char* pstr) : _pstr(new char[strlen(pstr) + 1]()) {
	std::cout << "String::String constructor" << std::endl;
	strcpy(_pstr, pstr);
}

String::String(const String& pstr) : _pstr(new char[strlen(pstr._pstr) + 1]()) {
	std::cout << "String::String copy constructor" << std::endl;
	strcpy(_pstr, pstr._pstr);
}


std::istream& operator>>(std::istream& is, String& s) {
	std::string buffer;
	is >> buffer;
	delete[] s._pstr;
	s._pstr = new char[strlen(buffer.c_str()) + 1]();
	strcpy(s._pstr, buffer.c_str());
	return is;
}

String& String::operator=(const String& pstr) {
	if (this->_pstr == pstr.c_str()) {
		return *this;
	}
	auto temp = new char[strlen(pstr.c_str()) + 1]();
	strcpy(temp, pstr.c_str());
	delete[] this->_pstr;
	this->_pstr = temp;
	return *this;
}

String& String::operator=(const char* pstr) {
	if (this->_pstr == pstr) {
		return *this;
	}
	auto temp = new char[strlen(pstr) + 1]();
	strcpy(temp, pstr);
	delete[] this->_pstr;
	this->_pstr = temp;
	return *this;
}

String& String::operator+=(const String& pstr) {
	const size_t old = strlen(this->_pstr);
	const size_t new_size = old + strlen(pstr.c_str()) + 1;
	auto buffer = new char[new_size]();
	strcpy(buffer, this->_pstr);
	strcat(buffer, pstr.c_str());
	delete[] this->_pstr;
	this->_pstr = buffer;
	return *this;
}

String& String::operator+=(const char* pstr) {
	const size_t old = strlen(this->_pstr);
	const size_t new_size = old + strlen(pstr) + 1;
	auto buffer = new char[new_size]();
	strcpy(buffer, this->_pstr);
	strcat(buffer, pstr);
	delete[] this->_pstr;
	this->_pstr = buffer;
	return *this;
}

std::size_t String::size() const {
	return strlen(this->_pstr);
}

char& String::operator[](std::size_t index) {
	if (index >= this->size()) {
		static char nullChar = '\0';
		return nullChar;
	}
	return this->_pstr[index];
}

const char& String::operator[](std::size_t index) const {
	if (index >= this->size()) {
		static char nullChar = '\0';
		return nullChar;
	}
	return this->_pstr[index];
}

bool operator==(const String& data1, const String& data2) {
	if (data1.size() != data2.size()) {
		return false;
	}
	for (size_t i = 0; i < data1.size(); i++) {
		if (data1.c_str()[i] != data2.c_str()[i]) {
			return false;
		}
	}

	return true;
}

bool operator!=(const String& data1, const String& data2) {
	return !(data1 == data2);
}

bool operator<(const String& data1, const String& data2) {
	size_t minSize = std::min(data1.size(), data2.size());
	for (size_t i = 0; i < minSize; i++) {
		if (data1.c_str()[i] < data2.c_str()[i]) {
			return true;
		}
		if (data1.c_str()[i] > data2.c_str()[i]) {
			return false;
		}
	}
	return data1.size() < data2.size();
}

bool operator>(const String& data1, const String& data2) {
	return data2 < data1;
}

bool operator<=(const String& data1, const String& data2) {
	return !(data1 > data2);
}

bool operator>=(const String& data1, const String& data2) {
	return !(data1 < data2);
}

String operator+(const String& string, const String& string1) {
	String string2(string);
	return string2 += string1;
}

String operator+(const String& string, const char* text) {
	String string1(string);
	return string1 += text;
}

String operator+(const char* string, const String& string1) {
	String string2(string);
	return string2 += string1.c_str();
}

void testDefaultConstructor() {
	String str;
	assert(str.size() == 0);
	assert(strcmp(str.c_str(), "") == 0);
	std::cout << "Default constructor test passed!" << std::endl;
}

void testParameterizedConstructor() {
	String str("Hello");
	assert(str.size() == 5);
	assert(strcmp(str.c_str(), "Hello") == 0);
	std::cout << "Parameterized constructor test passed!" << std::endl;
}

void testCopyConstructor() {
	String str1("Copy me");
	String str2(str1);
	assert(str2.size() == str1.size());
	assert(strcmp(str2.c_str(), str1.c_str()) == 0);
	std::cout << "Copy constructor test passed!" << std::endl;
}

void testAssignmentOperator() {
	String str1("Assign me");
	String str2;
	str2 = str1;
	assert(str2.size() == str1.size());
	assert(strcmp(str2.c_str(), str1.c_str()) == 0);
	std::cout << "Assignment operator test passed!" << std::endl;
}

void testAssignmentOperatorWithCStr() {
	String str;
	str = "C-string";
	assert(str.size() == 8);
	assert(strcmp(str.c_str(), "C-string") == 0);
	std::cout << "Assignment operator with C-string test passed!" << std::endl;
}

void testConcatenationOperator() {
	String str1("Hello, ");
	String str2("world!");
	str1 += str2;
	assert(strcmp(str1.c_str(), "Hello, world!") == 0);
	std::cout << "Concatenation operator test passed!" << std::endl;
}

void testConcatenationOperatorWithCStr() {
	String str1("Hello, ");
	str1 += "world!";
	assert(strcmp(str1.c_str(), "Hello, world!") == 0);
	std::cout << "Concatenation operator with C-string test passed!" << std::endl;
}

void testAdditionOperator() {
	String str1("Hello, ");
	String str2("world!");
	String result = str1 + str2;
	assert(strcmp(result.c_str(), "Hello, world!") == 0);
	std::cout << "Addition operator test passed!" << std::endl;
}

void testAdditionOperatorWithCStr() {
	String str1("Hello, ");
	String result = str1 + "world!";
	assert(strcmp(result.c_str(), "Hello, world!") == 0);
	std::cout << "Addition operator with C-string test passed!" << std::endl;
}

void testIndexOperator() {
	String str("Index test");
	assert(str[0] == 'I');
	assert(str[5] == 'x');
	assert(str[10] == '\0'); // Out of bounds check, should return nullChar
	std::cout << "Index operator test passed!" << std::endl;
}

void testComparisonOperators() {
	String str1("abc");
	String str2("abc");
	String str3("abcd");
	String str4("abb");

	assert(str1 == str2);
	assert(str1 != str3);
	assert(str1 < str3);
	assert(str4 < str1);
	assert(str3 > str1);
	assert(str1 <= str2);
	assert(str1 <= str3);
	assert(str3 >= str1);
	assert(str1 >= str2);

	std::cout << "Comparison operators test passed!" << std::endl;
}

void testStreamOperators() {
	String str1("Stream test");
	std::stringstream ss;
	ss << str1;
	assert(ss.str() == "Stream test");

	String str2;
	ss >> str2;
	assert(strcmp(str2.c_str(), "Stream") == 0); // Only first word is extracted

	std::cout << "Stream operators test passed!" << std::endl;
}

void test_10_01() {
	String str1; //无参

	String str2 = String("Hello,world");
	std::cout << str2 << endl;
	String str3("wangdao"); //有参
	std::cout << str3 << endl;

	String str4 = str3; //拷贝
	cout << str4 << endl;

	str4 = str2; //赋值
	cout << str4 << endl;

	str2 += str3;
	cout << str2 << endl;

	char a[] = "aa";
	str1 += a;
	cout << str1 << endl;
	testDefaultConstructor();
	testParameterizedConstructor();
	testCopyConstructor();
	testAssignmentOperator();
	testAssignmentOperatorWithCStr();
	testConcatenationOperator();
	testConcatenationOperatorWithCStr();
	testAdditionOperator();
	testAdditionOperatorWithCStr();
	testIndexOperator();
	testComparisonOperators();
	testStreamOperators();
}

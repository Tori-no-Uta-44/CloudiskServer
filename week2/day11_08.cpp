//
// Created by 李勃鋆 on 24-8-25.
//
#include "../week02.h"

class CowString {
public:
	CowString();

	explicit CowString(const char *pstr);

	~CowString();

	CowString(const CowString &rhs);

	CowString &operator=(const CowString &rhs);

	char &operator[](size_t idx);

	size_t size() const {
		return strlen(_pstr);
	}

	const char *c_str() const {
		return _pstr;
	}

	int use_count() const {
		return *reinterpret_cast<int *>(_pstr - kRefcountLength);
	}

	friend
	ostream &operator<<(ostream &os, const CowString &rhs);

private:
	char *malloc(const char *pstr = nullptr) {
		if (pstr) {
			return new char[strlen(pstr) + 1 + kRefcountLength]() + kRefcountLength;
		}
		return new char[1 + kRefcountLength]() + kRefcountLength;
	}

	void release() {
		decreaseRefcount();
		if (use_count() == 0) {
			delete [] (_pstr - kRefcountLength);
			cout << ">> delete heap" << endl;
		}
		_pstr = nullptr;
	}


	void initRefcount() {
		*reinterpret_cast<int *>(_pstr - kRefcountLength) = 1;
	}

	void increaseRefcount() {
		++*reinterpret_cast<int *>(_pstr - kRefcountLength);
	}

	void decreaseRefcount() {
		--*reinterpret_cast<int *>(_pstr - kRefcountLength);
	}

	static const int kRefcountLength = 4;
	char *_pstr;
};

ostream &operator<<(ostream &os, const CowString &rhs) {
	os << rhs._pstr;
	return os;
}

CowString::CowString():
	_pstr(malloc()) {
	cout << "CowString()" << endl;
	initRefcount();
}

CowString::CowString(const char *pstr):
	_pstr(malloc(pstr)) {
	cout << "CowString(const char *)" << endl;
	strcpy(_pstr, pstr);
	initRefcount();
}

CowString::~CowString() {
	cout << "~CowString()" << endl;
	release();
}

CowString::CowString(const CowString &rhs):
	_pstr(rhs._pstr) {
	cout << "CowString拷贝构造" << endl;
	increaseRefcount();
}

CowString &CowString::operator=(const CowString &rhs) {
	if (this != &rhs) {
		//自赋值的判断
		release(); //尝试回收原本的空间
		_pstr = rhs._pstr; //浅拷贝
		increaseRefcount(); //新空间的引用计数+1
	}
	return *this;
}

#if 0
char & CowString::operator[](size_t idx){
    if(idx < size()){
        return _pstr[idx];
    }else{
        cout << "out of range" << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}
#endif

char &CowString::operator[](size_t idx) {
	if (idx < size()) {
		if (use_count() > 1) {
			//原本空间的引用计数-1
			decreaseRefcount();
			//深拷贝
			char *temp = malloc(_pstr);
			strcpy(temp, _pstr);
			//修改指向
			_pstr = temp;
			//初始化新空间的引用计数
			initRefcount();
		}
		return _pstr[idx];
	}
	else {
		cout << "out of range" << endl;
		static char nullchar = '\0';
		return nullchar;
	}
}

void test_11_08() {
	CowString str1("world");
	CowString str2 = str1;
	cout << str1[0] << endl;
	str1[0] = 'W';
	cout << str1 << endl;
	cout << str2 << endl;
	cout << "str1.use_count:" << str1.use_count() << endl;
	cout << "str2.use_count:" << str2.use_count() << endl;
}

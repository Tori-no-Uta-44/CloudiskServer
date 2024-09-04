//
// Created by 李勃鋆 on 24-9-3.
//
#include <utility>

#include "../week04.h"

void test20_1() {
	//将一个list中的char *指针元素赋值给一个vector中的string。
	list<const char *> lst = {"hello", "world", "!"};
	vector<string> v;
	auto it = lst.begin();
	v.emplace_back(*it);
	++it;
	v.emplace_back(*it);
	for (auto &i : v) {
		cout << i << endl;
	}
}

void test20_2() {
	deque<string> d;
	string s;
	for (int i = 0; i < 2; i++) {
		std::cin >> s;
		d.push_back(s);
	}
	string s1;
	std::cin >> s1;
	d.emplace_back(s1);
	string s2;
	std::cin >> s2;
	d.emplace_front(s2);
	string s3;
	std::cin >> s3;
	d.push_front(s3);
	for (auto &it : d) {
		cout << it << "\t";
	}
	cout << endl;
}

void test20_3() {
	list<int> l = {1, 2, 3};
	deque<int> a;
	deque<int> b;
	for (auto &i : l) {
		if (i % 2 == 0) {
			a.emplace_back(i);
		}
		else {
			b.push_back(i);
		}
	}
	for (auto &i : a) {
		cout << i << "\t";
	}
	cout << endl;
	for (auto &i : b) {
		cout << i << "\t";
	}
	cout << endl;
	for (auto l1 : l) {
		cout << l1 << "\t";
	}
	cout << endl;
}

class Stu_20 {
public:
	Stu_20() = default;

	Stu_20(string name, int age, double cScore, double mScore, double eScore):
		_name(std::move(name)), _age(age), _cScore(cScore), _mScore(mScore), _eScore(eScore) {

	}

	friend ostream &operator<<(ostream &out, const Stu_20 &s);

	[[nodiscard]] double get_c_score() const {
		return _cScore;
	}

	[[nodiscard]] double get_m_score() const {
		return _mScore;
	}

	[[nodiscard]] double get_e_score() const {
		return _eScore;
	}

private:
	string _name;
	int _age = 0;
	double _cScore = 0;
	double _mScore = 0;
	double _eScore = 0;
};

ostream &operator<<(ostream &out, const Stu_20 &s) {
	out << s._name << "-" << s._age << "-" << s._cScore << "-" << s._mScore << "-" << s._eScore << "\t";
	return out;
}

bool CompareStu_20(const Stu_20 &s1, const Stu_20 &s2) {
	double sum1 = 0.0;
	double sum2 = 0.0;
	sum1 = s1.get_c_score() + s1.get_m_score() + s1.get_e_score();
	sum2 = s2.get_c_score() + s2.get_m_score() + s2.get_e_score();
	if (sum1 == sum2) {
		return s1.get_c_score() > s2.get_c_score();
	}
	return sum1 > sum2;
}

void test20_4() {
	//按照总成绩sum进行降序，如果总成绩sum相同按照语文成绩进行降序
	Stu_20 s1("aa", 1, 1.1, 1.2, 1.3);
	Stu_20 s2("bb", 2, 2.2, 2.3, 2.4);
	Stu_20 s3("cc", 3, 3.3, 3.4, 3.1);
	list<Stu_20> l = {s1, s2, s3};
	l.sort(CompareStu_20);
	for (auto &i : l) {
		cout << i << endl;
	}
}

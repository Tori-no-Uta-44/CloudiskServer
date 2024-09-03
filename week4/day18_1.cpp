//
// Created by 李勃鋆 on 24-9-2.
//
#include <utility>

#include "../week04.h"

void test18_1() {
	vector<int> num1;
	vector<int> num2(5, 1);
	vector<int> num3(num2.begin(), num2.end());
	vector<int> num4 = {1, 2, 3};
	vector<int> num5(num4);
	for (auto &n2 : num2) {
		cout << n2 << endl;
	}
	for (auto &n3 : num3) {
		cout << n3 << endl;
	}
	for (auto &n4 : num4) {
		cout << n4 << endl;
	}
	for (int &it : num1) {
		cout << it << "\t";
	}
}

void test18_2() {
	deque<int> num1;
	deque<int> num2(5, 1);
	deque<int> num3(num2.begin(), num2.end());
	deque<int> num4 = {1, 2, 3};
	deque<int> num5(num4);
	for (auto &n2 : num2) {
		cout << n2 << endl;
	}
	for (auto &n3 : num3) {
		cout << n3 << endl;
	}
	for (auto &n4 : num4) {
		cout << n4 << endl;
	}
	for (auto &n5 : num5) {
		cout << n5 << endl;
	}
}

void test18_3() {
	list<int> num1;
	list<int> num2(5, 1);
	list<int> num3(num2.begin(), num2.end());
	list<int> num4 = {1, 2, 3};
	list<int> num5(num4);
	for (auto &n2 : num2) {
		cout << n2 << endl;
	}
	for (auto &n3 : num3) {
		cout << n3 << endl;
	}
	for (auto &n4 : num4) {
		cout << n4 << endl;
	}
	for (auto &n5 : num5) {
		cout << n5 << endl;
	}
}

class Person_18 {
public:
	string _name;
	int _score = 0;

	Person_18();

	explicit Person_18(string name, int score = 0):
		_name(std::move(name)) {

	}
};

void test18_4() {
	Person_18 personA("aa");
	Person_18 personB("bb");
	Person_18 personC("cc");
	Person_18 personD("dd");
	Person_18 personE("ee");
	vector<Person_18> persons = {personA, personB, personC, personD};
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(1, 100);
	for (auto &person : persons) {
		deque<int> scores;
		for (int i = 0; i < 10; i++) {
			scores.push_back(distribution(generator));
		}
		sort(scores.begin(), scores.end());
		for (int i = 1; i < 9; i++) {
			person._score += scores[i];
		}
		person._score = person._score / 8;
	}
	for (auto &[_name,_score] : persons) {
		std::cout << _name << "--" << _score << "\t";
	}
}

void test18_5() {
	vector<char> vc = {'H', 'E', 'L', 'L', 'O'};
	for (auto &vc1 : vc) {
		cout << vc1;
	}
	std::string s = "word";
	std::vector<char> vc2(s.c_str(), s.c_str() + s.size() + 1);
	std::string s3 = "word";
	std::vector<char> vc3;
	vc3.assign(s.begin(), s.end());
}

void test18_6() {
	vector<vector<int>> a(9);
	// for (int i = 1; i <= 9; i++) {
	// 	vector<int> b;
	// 	for (int j = 1; j <= i; j++) {
	// 		std::cout << j<<"*"<<i<<"="<<j*i<<"\t";
	// 		b.push_back(j*i);
	// 	}
	// 	a.push_back(b);
	// 	std::cout << std::endl;
	// }
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= i; j++) {
			a[i - 1].push_back(j * i);
		}
	}
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= i; j++) {
			cout << j << "*" << i << "=" << a[i - 1][j - 1] << "\t";
		}
		cout << endl;
	}
}

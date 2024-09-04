//
// Created by 李勃鋆 on 24-9-4.
//
#include "../week04.h"

void test21_1() {
	list<int> list1 = {1, 2, 3, 5, 6};
	list1.sort();
	for (auto &i : list1) {
		cout << i << endl;
	}
	list1.reverse();
	for (auto &i : list1) {
		cout << i << endl;
	}
	list<int> list2 = {7, 7, 7, 8, 9, 9, 22, 11};
	list2.sort();
	for (auto &i : list2) {
		cout << i << endl;
	}
	list1.merge(list2);
	list1.unique();
	for (auto &i : list1) {
		cout << i << endl;
	}
	std::list<int> list3{10, 20, 30, 40, 50};
	auto it = list2.begin();
	advance(it, 2);
	list1.splice(it, list3);
	for (auto &i : list1) {
		cout << i << endl;
	}
}

class Point21 {
public:
	Point21() = default;

	Point21(double x, double y):
		_x(x), _y(y) {

	}

	[[nodiscard]] double get_x() const {
		return _x;
	}

	[[nodiscard]] double get_y() const {
		return _y;
	}

	friend ostream &operator<<(ostream &out, const Point21 &p);

	friend bool operator<(const Point21 &p1, const Point21 &p2);

	friend bool operator==(const Point21 &p1, const Point21 &p2);

private:
	double _x;
	double _y;
};

bool operator<(const Point21 &p1, const Point21 &p2) {
	cout << "operator<" << endl;
	if (p1._x < p2._x) {
		return true;
	}
	if (p1._x > p2._x) {
		return false;
	}
	if (p1._x == p2._x) {
		if (p1._y == p2._y) {
			return false;
		}
	}
	return p1._y < p2._y;
}

bool operator==(const Point21 &p1, const Point21 &p2) {
	cout << "operator==" << endl;
	if (p1._x == p2._y) {
		if (p1._y == p2._y) {
			return true;
		}
	}
	return false;
}

ostream &operator<<(ostream &out, const Point21 &p) {
	out << p._x << "-" << p._y << "\t";
	return out;
}

struct ComparePoint21 {
	bool operator()(const Point21 &p1, const Point21 &p2) const {
		cout << "out,operator()" << endl;
		if (p1.get_x() < p2.get_x()) {
			return true;
		}
		if (p1.get_x() > p2.get_x()) {
			return false;
		}
		if (p1.get_x() == p2.get_x()) {
			if (p1.get_y() == p2.get_y()) {
				return false;
			}
		}
		return p1.get_y() < p2.get_y();
	}
};

template <>
struct std::greater<Point21> {
	bool operator()(const Point21 &p1, const Point21 &p2) const {
		cout << "template,operator()" << endl;
		if (p1.get_x() > p2.get_x()) {
			return true;
		}
		if (p1.get_x() < p2.get_x()) {
			return false;
		}
		if (p1.get_x() == p2.get_x()) {
			if (p1.get_y() == p2.get_y()) {
				return false;
			}
		}
		return p1.get_y() > p2.get_y();
	}
};

void test21_2() {
	Point21 p1 = {1, 2};
	Point21 p2 = {1, 2};
	Point21 p3 = {1, 4};
	Point21 p4 = {9, 46};
	set<Point21> set1 = {p1, p2, {5, 7}};
	set1.insert(p3);
	set1.insert(p4);
	set1.insert(Point21(0, 0));
	for (auto &i : set1) {
		cout << i << std::endl;
	}

	set<Point21, ComparePoint21> set2 = {p1, p2, {5, 7}};
	set1.insert(p3);
	set1.insert(p4);
	set1.insert(Point21(0, 0));

	set<Point21, greater<Point21>> set3 = {p1, p2, {5, 7}};
	set1.insert(p3);
	set1.insert(p4);
	set1.insert(Point21(0, 0));
}

void test21_3() {
	int a, b;
	std::cin >> a >> b;
	set<int> set1;
	for (int i = 0; i < a; i++) {
		int c;
		std::cin >> c;
		set1.insert(c);
	}
	for (int i = 0; i < b; i++) {
		int c;
		std::cin >> c;
		set1.insert(c);
	}
	for (auto &i : set1) {
		cout << i << "\t";
	}
}

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

	Points(int ix, int iy = 0): _ix(ix), _iy(iy) {
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

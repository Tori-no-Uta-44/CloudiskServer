//
// Created by 李勃鋆 on 24-8-29.
//
#include "../week03.h"

namespace demo16_01 {
	template <class T>
	T add(T t1, T t2) {
		return t1 + t2;
	}

	template <class T>
	struct StackNode {
		T val;
		StackNode *next;
	};

	template <class T>
	class Stack {
	public:
		[[nodiscard]] bool empty() const {
			return size == 0;
		}

		void push(T data) {
			auto *node = new StackNode<T>;
			node->val = data;
			node->next = stack_node;
			stack_node = node;
			size++;
		}

		void pop() {
			if (!empty()) {
				auto *node = stack_node;
				stack_node = stack_node->next;
				delete node;
				size--;
			}
		}

		[[nodiscard]] T top() const {
			return stack_node->val;
		}

		StackNode<T> *stack_node;
		int size;

		Stack():
			stack_node(nullptr), size(0) {
		}
	};
}

void test16_01() {
	using namespace demo16_01;
	std::cout << add(0, 1) << endl;
	std::cout << add(3.4, 4.5) << endl;
	set<int> num1 = {6, 7};
	set<int> num2 = {8, 9};
	for (auto &i : num1) {
		for (auto &j : num2) {
			std::cout << add(i, j) << '\t';
		}
		std::cout << endl;
	}
}

void test16_02() {
	using namespace demo16_01;
	Stack<int> s;
	s.push(10);
	s.push(20);

	while (!s.empty()) {
		std::cout << "Top: " << s.top() << std::endl;
		s.pop();
	}
}

template <class T>
T add(T t) {
	return t;
}

template <class T, class... Args>
T add(T t, Args... args) {
	return t + add(args...);
}

void test16_03() {
	std::cout << add(1.2, 3.4, 5) << std::endl;
}

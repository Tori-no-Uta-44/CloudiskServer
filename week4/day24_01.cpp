//
// Created by 李勃鋆 on 24-9-10.
//
#include "../week01.h"
#include "../week04.h"

namespace day24 {
	template <typename T>
	class Vector {
	public:
		Vector():
			_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {

		}

		~Vector();

		void push_back(const T &data) {
			if (size() >= capacity()) {
				reallocate();
			}
			_alloc.construct(_finish++, data);
		}

		void pop_back() {
			if (size() > 0) {
				_alloc.destroy(--_finish);
			}
		}

		int size() {
			return _finish - _start;
		}

		int capacity() {
			return _end_of_storage - _start;
		}

	private:
		void reallocate() //重新分配内存,动态扩容要用的
		{
			int news = capacity() == 0 ? capacity() * 2 : 1;
			T *new_start = _alloc.allocate(news);
			T *new_finish = new_start;
			for (auto i = _start; i != _finish; ++i) {
				_alloc.construct(new_finish++, move(*i));
				_alloc.destroy(i);
			}
			if (_start) {
				_alloc.destroy(_start);
			}
			_start = new_start;
			_finish = new_finish;
			_end_of_storage = new_start + news;
		}

	private:
		static std::allocator<T> _alloc;
		T *_start; //指向数组中的第一个元素
		T *_finish; //指向最后一个实际元素之后的那个元素
		T *_end_of_storage; //指向数组本身之后的位置
	};
}

template <typename T>
std::allocator<T> day24::Vector<T>::_alloc;

void test24_01() {
	day24::Vector<int> v;
	v.push_back(0);
}

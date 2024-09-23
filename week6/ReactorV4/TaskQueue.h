//
// Created by 李勃鋆 on 24-9-14.
//

#ifndef STASKQUEUE_H
#define STASKQUEUE_H
#include "Task.h"
#include "../../week01.h"

namespace ReactorV4 {
	class Task;
	using T = unique_ptr<Task>;

	class TaskQueue {
	public:
		void push(T &&data);

		T pop();

		void wakeup();

		TaskQueue(const TaskQueue &data) = delete;

		TaskQueue &operator=(const TaskQueue &data) = delete;

		[[nodiscard]] bool isEmpty();

		TaskQueue();

		explicit TaskQueue(size_t capacity);

		~TaskQueue();

	private:
		size_t _capacity = 8;
		deque<T> _queue;
		mutex _mutex;
		condition_variable _isFull;
		condition_variable _isEmpty;
		bool _flag = true;
	};
}

#endif //STASKQUEUE_H

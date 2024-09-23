//
// Created by 李勃鋆 on 24-9-14.
//

#ifndef STASKQUEUE_H
#define STASKQUEUE_H
#include "../week5.h"
#include "Task.h"
namespace day30_1 {
	class Task;
	using T = unique_ptr<Task>;

	class TaskQueue {
	public:
		void push(T&& data);

		T pop();

		void wakeup();

		static TaskQueue *getInstance();

		TaskQueue(const TaskQueue &data) = delete;

		TaskQueue &operator=(const TaskQueue &data) = delete;

		[[nodiscard]] bool isEmpty() const;

	private:
		TaskQueue() = default;

		explicit TaskQueue(size_t capacity);

		static void destroyInstance();

		~TaskQueue();

		size_t _capacity = 8;
		deque<T> _queue;
		mutex _mutex;
		condition_variable _isFull;
		condition_variable _isEmpty;
		std::atomic<bool> _flag;
		static TaskQueue *_task_queue;
		static once_flag _once_flag;
	};
}

#endif //STASKQUEUE_H

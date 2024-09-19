//
// Created by 李勃鋆 on 24-9-14.
//
#include "STaskQueue.h"

day30_1::TaskQueue *day30_1::TaskQueue::_task_queue = nullptr;

once_flag day30_1::TaskQueue::_once_flag;

void day30_1::TaskQueue::push(T&& data) {
	unique_lock<mutex> lock(_mutex);
	std::cout << "Pushing task to queue" << std::endl;
	while (_queue.size() == _capacity) {
		_isFull.wait(lock);
	}
	_queue.emplace_back(std::move(data));
	cout << "Pushed task to queue" << std::endl;
	_isEmpty.notify_one();
}


day30_1::T day30_1::TaskQueue::pop() {
	std::unique_lock<std::mutex> lock(_mutex);
	while (_queue.empty() && _flag) {
		_isEmpty.wait(lock);
	}

	if (!_queue.empty()) {
		T data = std::move(_queue.front());
		_queue.pop_front();
		_isFull.notify_one();

		// 调试输出
		std::cout << "Popping task from queue" << std::endl;

		return data;
	} else {
		cout << "TaskQueue::pop(): No more tasks, returning nullptr" << std::endl;
		// 队列为空且线程池已停止
		return nullptr;
	}
}


void day30_1::TaskQueue::wakeup() {
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_flag = false;
	}
	_isEmpty.notify_all();
}


day30_1::TaskQueue *day30_1::TaskQueue::getInstance() {
	call_once(_once_flag, []() {
		_task_queue = new TaskQueue(8);
		atexit(destroyInstance);
	});
	return _task_queue;
}

day30_1::TaskQueue::~TaskQueue() {
	cout << "TaskQueue::~TaskQueue()" << endl;
}


day30_1::TaskQueue::TaskQueue(size_t capacity):
	_capacity(capacity) {
	cout << "TaskQueue::TaskQueue() " <<capacity<< endl;
}

void day30_1::TaskQueue::destroyInstance() {
	if (_task_queue != nullptr) {
		delete _task_queue;
		_task_queue = nullptr;
	}
}

bool day30_1::TaskQueue::isEmpty() const {
	return _queue.empty();
}

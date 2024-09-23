//
// Created by 李勃鋆 on 24-9-14.
//
#include "TaskQueue.h"

void ReactorV4::TaskQueue::push(T &&data) {
	unique_lock<mutex> lock(_mutex);
	std::cout << "Pushing task to queue" << std::endl;
	while (_queue.size() == _capacity) {
		_isFull.wait(lock);
	}
	_queue.emplace_back(std::move(data));
	cout << "Pushed task to queue" << std::endl;
	_isEmpty.notify_one();
}


ReactorV4::T ReactorV4::TaskQueue::pop() {
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
	}
	cout << "TaskQueue::pop(): No more tasks, returning nullptr" << std::endl;
	// 队列为空且线程池已停止
	return nullptr;
}


void ReactorV4::TaskQueue::wakeup() {
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_flag = false;
	}
	_isEmpty.notify_all();
}

ReactorV4::TaskQueue::~TaskQueue()=default;


ReactorV4::TaskQueue::TaskQueue(size_t capacity):
	_capacity(capacity) {

}

bool ReactorV4::TaskQueue::isEmpty() {
	std::unique_lock<std::mutex> lock(_mutex);
	return _queue.empty();
}

ReactorV4::TaskQueue::TaskQueue() = default;

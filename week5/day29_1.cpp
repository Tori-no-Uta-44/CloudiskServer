//
// Created by 李勃鋆 on 24-9-13.
//
#include <condition_variable>

#include "../week5.h"

namespace day29 {
	template <class T=int>
	class BlockQueue {
		long _capacity = 0;
		deque<T> _queue;
		mutex _mutex;
		condition_variable _notEmpty;
		condition_variable _notFull;;

	public:
		BlockQueue() = default;

		explicit BlockQueue(long capacity):
			_capacity(capacity) {

		}

		void push(const T &data) {
			unique_lock<mutex> lock(_mutex);
			while (_queue.size() == _capacity) {
				_notFull.wait(lock); // 等待队列有空位
			}
			_queue.push_back(data);
			_notEmpty.notify_all(); // 通知消费者
		}

		T pop() {
			unique_lock<mutex> lock(_mutex);
			while (_queue.empty()) {
				_notEmpty.wait(lock); // 等待队列不空
			}
			T data = _queue.front();
			_queue.pop_front();
			_notFull.notify_all(); // 通知生产者
			return data;
		}

		BlockQueue(const BlockQueue &other) = delete;

		BlockQueue &operator=(const BlockQueue &other) = delete;

		~BlockQueue() = default;
	};

	class Producer {
	public:
		Producer() = default;

		~Producer() = default;

		void produce(BlockQueue<> &queue) {
			std::random_device rd; // 使用随机设备生成种子
			std::mt19937_64 generator(rd());
			std::uniform_int_distribution<int> distribution(0, 100);
			for (int i = 0; i < 10; i++) {
				queue.push(distribution(generator));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	};

	class Consumer {
	public:
		void consume(BlockQueue<> &queue) {
			for (int i = 0; i < 10; i++) {
				cout << queue.pop() << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}
		}
	};
}

void test29_1() {
	using namespace day29;
	BlockQueue<> queue(5);
	Producer producer;
	Consumer consumer;
	thread t1(&Producer::produce, &producer, ref(queue));
	thread t2(&Consumer::consume, &consumer, ref(queue));
	t1.join();
	t2.join();
}

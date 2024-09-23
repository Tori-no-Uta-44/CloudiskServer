//
// Created by 李勃鋆 on 24-9-14.
//

#ifndef SThreadPool_H
#define SThreadPool_H
#include "TaskQueue.h"
#include "Task.h"
#include "../../week01.h"
#include "AbstractColor.h"
#include "AbstractShape.h"

namespace ReactorV4 {
	class ThreadPool {
	public:
		using T = std::unique_ptr<Task>;

		ThreadPool(size_t threadNum, size_t queSize);

		~ThreadPool();

		void run();

		void stop();

		void setTask(std::unique_ptr<Task> ptask);

		ThreadPool(const ThreadPool &data) = delete;

		ThreadPool &operator=(const ThreadPool &data) = delete;

	private:
		void runTask();

		T getTask();

		size_t _threadNum = 4;
		size_t _queSize = 8;
		std::vector<std::thread> _threads;
		TaskQueue _task_queue;
		std::atomic<bool> _stop;
	};
}

#endif //SThreadPool_H

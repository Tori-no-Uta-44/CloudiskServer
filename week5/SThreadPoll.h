//
// Created by 李勃鋆 on 24-9-14.
//

#ifndef STHREADPOLL_H
#define STHREADPOLL_H
#include "TaskQueue.h"
#include "Task.h"
#include "../week5.h"

namespace day30_1 {
	class ThreadPoll {
	public:
		using T = std::unique_ptr<Task>;

		static ThreadPoll* getInstance(size_t threadNum = 4, size_t queSize = 8);

		void run();
		void stop();
		void setTask(std::unique_ptr<Task> ptask);

		ThreadPoll(const ThreadPoll& data) = delete;
		ThreadPoll& operator=(const ThreadPoll& data) = delete;

	private:
		ThreadPoll(size_t threadNum, size_t queSize);
		~ThreadPoll();
		static void destroyInstance();

		void runTask();
		T getTask();

		size_t _threadNum;
		size_t _queSize;
		std::vector<std::thread> _threads;
		TaskQueue* _task_queue;
		std::atomic<bool> _stop;
		static ThreadPoll* _thread_poll;
		static std::once_flag _once_flag;
	};
}

#endif //STHREADPOLL_H

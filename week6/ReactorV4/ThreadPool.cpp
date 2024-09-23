//
// Created by 李勃鋆 on 24-9-14.
//

#include "ThreadPool.h"

namespace ReactorV4 {

    ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
        : _threadNum(threadNum), _queSize(queSize), _stop(false),_task_queue(queSize) {
    }

    ThreadPool::~ThreadPool() {
    	stop();
        std::cout << "ThreadPool::~ThreadPool" << std::endl;
    }

    void ThreadPool::run() {
        std::cout << "ThreadPool::run()" << std::endl;
        for (size_t i = 0; i < _threadNum; i++) {
            _threads.emplace_back(&ThreadPool::runTask, this);
        }
    }

    void ThreadPool::stop() {
        if (!_stop) {
            _stop = true;
            _task_queue.wakeup();
            for (auto &i : _threads) {
                if (i.joinable()) {
                    i.join();
                }
            }
        }
    }

    void ThreadPool::setTask(std::unique_ptr<Task> ptask) {
        if (ptask) {
            std::cout << "setTask: Adding task to queue" << std::endl;
            _task_queue.push(std::move(ptask));
        }
    }

    ThreadPool::T ThreadPool::getTask() {
        return _task_queue.pop();
    }

    void ThreadPool::runTask() {
        while (true) {
            T ptask = getTask();
            if (ptask) {
            	ptask->execute();
            } else {
            	// 如果任务为空，直接退出循环
            	std::cout << "ThreadPool::runTask: No more tasks, exiting thread" << std::endl;
            	break;
            }
        }
    }
}

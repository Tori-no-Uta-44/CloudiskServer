//
// Created by 李勃鋆 on 24-9-14.
//

#include "SThreadPoll.h"

#include "AbstractColor.h"
#include "AbstractShape.h"

namespace day30_1 {
    ThreadPoll* ThreadPoll::_thread_poll = nullptr;
    std::once_flag ThreadPoll::_once_flag;

    ThreadPoll* ThreadPoll::getInstance(size_t threadNum, size_t queSize) {
        std::call_once(_once_flag, [threadNum, queSize]() {
            _thread_poll = new ThreadPoll(threadNum, queSize);
            std::atexit(destroyInstance);
        });
        return _thread_poll;
    }

    ThreadPoll::ThreadPoll(size_t threadNum, size_t queSize)
        : _threadNum(threadNum), _queSize(queSize), _stop(false) {
        _task_queue = TaskQueue::getInstance();
    }

    ThreadPoll::~ThreadPoll() {
        std::cout << "ThreadPoll::~ThreadPoll" << std::endl;
    }

    void ThreadPoll::destroyInstance() {
        if (_thread_poll != nullptr) {
            delete _thread_poll;
            _thread_poll = nullptr;
        }
    }

    void ThreadPoll::run() {
        std::cout << "ThreadPoll::run()" << std::endl;
        for (size_t i = 0; i < _threadNum; i++) {
            _threads.emplace_back(&ThreadPoll::runTask, this);
        }
    }

    void ThreadPoll::stop() {
        if (!_stop) {
            _stop = true;
            _task_queue->wakeup();
            for (auto &i : _threads) {
                if (i.joinable()) {
                    i.join();
                }
            }
        }
    }

    void ThreadPoll::setTask(std::unique_ptr<Task> ptask) {
        if (ptask) {
            std::cout << "setTask: Adding task to queue" << std::endl;
            _task_queue->push(std::move(ptask));
        }
    }

    ThreadPoll::T ThreadPoll::getTask() {
        return _task_queue->pop();
    }

    void ThreadPoll::runTask() {
        while (true) {
            T ptask = getTask();
            if (ptask) {
                auto shape = ptask->getShape();
                auto color = ptask->getColor();
                if (shape && color) {
                    shape->draw();
                    std::cout << "area is " << shape->area() << std::endl;
                    color->fill();
                }
            } else {
                if (_stop) {
                    std::cout << "ThreadPoll::runTask: No more tasks, exiting thread" << std::endl;
                    break;
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
    }
}// day30_1

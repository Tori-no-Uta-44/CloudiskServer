//
// Created by 李勃鋆 on 24-9-14.
//
#include "SThreadPoll.h"
#include "Tasks.h"
#include "../week5.h"

void test30_1() {
	using namespace day30_1;
	ThreadPoll *threadPool = ThreadPoll::getInstance();
	threadPool->run();

	threadPool->setTask(std::make_unique<RectangleTask>());
	threadPool->setTask(std::make_unique<CircleTask>());
	std::this_thread::sleep_for(std::chrono::seconds(2));
	threadPool->stop();
}

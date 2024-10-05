//
// Created by 李勃鋆 on 24-9-27.
//
#include <sw/redis++/redis++.h>
#include "../week01.h"
#include "../week6.h"
void test_redis_link() {
	try {
		auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");
		redis.set("key", "value");
		auto val = redis.get("key");
		if (val) {
			std::cout << *val << std::endl;
		}
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
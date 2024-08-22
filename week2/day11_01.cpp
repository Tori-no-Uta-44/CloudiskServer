//
// Created by 李勃鋆 on 24-8-23.
//
#include "../week02.h"

class Singleton_test_11_01 {
public:
	friend class AutoRelease;

	Singleton_test_11_01(const Singleton_test_11_01& log) = delete;

	Singleton_test_11_01& operator=(const Singleton_test_11_01& log) = delete;

	void debug(const std::string& data) const {
		_category->debug(
			"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
			std::to_string(__LINE__) + " - " + data);
	}

	static Singleton_test_11_01* getInstance() {
		if (_p_log_11_01 == nullptr) {
			_p_log_11_01 = new Singleton_test_11_01();
		}

		return _p_log_11_01;
	}

private:
	Singleton_test_11_01() {
		_appender = new log4cpp::OstreamAppender("console", &std::cout);
		auto* layout = new log4cpp::PatternLayout();
		layout->setConversionPattern("%d [%c] [%p] - %m%n");
		_appender->setLayout(layout);

		_category = &log4cpp::Category::getRoot();
		_category->addAppender(_appender);
		_category->setPriority(log4cpp::Priority::DEBUG); // 默认优先级设置为 DEBUG
	}

	~Singleton_test_11_01() {
		log4cpp::Category::shutdown();
	}

	static void initSingleton() {
		_p_log_11_01 = new Singleton_test_11_01();
	}

	log4cpp::Appender* _appender;
	log4cpp::Category* _category;

	static Singleton_test_11_01* _p_log_11_01;
};

Singleton_test_11_01* Singleton_test_11_01::_p_log_11_01 = nullptr;

class AutoRelease {
public:
	explicit AutoRelease(Singleton_test_11_01* p): _p(p) {
	}

	~AutoRelease() {
		if (_p != nullptr) {
			delete _p;
			_p = nullptr;
		}
	}

private:
	Singleton_test_11_01* _p;
};

void test_11_01() {
	AutoRelease auto_release(Singleton_test_11_01::getInstance());
	Singleton_test_11_01::getInstance()->debug("The log is a debug message");
}

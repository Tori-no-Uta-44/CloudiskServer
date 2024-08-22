//
// Created by 李勃鋆 on 24-8-23.
//
#include "../week02.h"

class Singleton_test_11_03 {
public:
	Singleton_test_11_03(const Singleton_test_11_03& log) = delete;

	Singleton_test_11_03& operator=(const Singleton_test_11_03& log) = delete;

	void debug(const std::string& data) const {
		_category->debug(
			"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
			std::to_string(__LINE__) + " - " + data);
	}

	static Singleton_test_11_03* getInstance() {
		if (_p_log_11_03 == nullptr) {
			atexit(destroyInstance);
			_p_log_11_03 = new Singleton_test_11_03();
		}

		return _p_log_11_03;
	}

private:
	Singleton_test_11_03() {
		_appender = new log4cpp::OstreamAppender("console", &std::cout);
		auto* layout = new log4cpp::PatternLayout();
		layout->setConversionPattern("%d [%c] [%p] - %m%n");
		_appender->setLayout(layout);

		_category = &log4cpp::Category::getRoot();
		_category->addAppender(_appender);
		_category->setPriority(log4cpp::Priority::DEBUG); // 默认优先级设置为 DEBUG
	}

	~Singleton_test_11_03() {
		log4cpp::Category::shutdown();
	}

	static void initSingleton() {
		_p_log_11_03 = new Singleton_test_11_03();
	}

	static void destroyInstance() {
		if (_p_log_11_03!=nullptr) {
			delete _p_log_11_03;
			_p_log_11_03 = nullptr;
		}
	}

	log4cpp::Appender* _appender;
	log4cpp::Category* _category;

	static Singleton_test_11_03* _p_log_11_03;
};

Singleton_test_11_03* Singleton_test_11_03::_p_log_11_03 = Singleton_test_11_03::getInstance();

void test_11_03() {
	Singleton_test_11_03::getInstance()->debug("The log is a debug message");
}

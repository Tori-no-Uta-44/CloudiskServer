//
// Created by 李勃鋆 on 24-8-23.
//
#include "../week02.h"

class Singleton_test_11_04 {
public:
	Singleton_test_11_04(const Singleton_test_11_04& log) = delete;

	Singleton_test_11_04& operator=(const Singleton_test_11_04& log) = delete;

	void debug(const std::string& data) const {
		_category->debug(
			"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
			std::to_string(__LINE__) + " - " + data);
	}

	static Singleton_test_11_04* getInstance() {
		pthread_once(&_oncePthreadOnce, &init);
		return _p_log_11_04;
	}

private:
	static void init() {
		_p_log_11_04 = new Singleton_test_11_04();
		atexit(destroyInstance);
	}

	Singleton_test_11_04() {
		_appender = new log4cpp::OstreamAppender("console", &std::cout);
		auto* layout = new log4cpp::PatternLayout();
		layout->setConversionPattern("%d [%c] [%p] - %m%n");
		_appender->setLayout(layout);

		_category = &log4cpp::Category::getRoot();
		_category->addAppender(_appender);
		_category->setPriority(log4cpp::Priority::DEBUG); // 默认优先级设置为 DEBUG
	}

	~Singleton_test_11_04() {
		log4cpp::Category::shutdown();
	}

	static void initSingleton() {
		_p_log_11_04 = new Singleton_test_11_04();
	}

	static void destroyInstance() {
		if (_p_log_11_04 != nullptr) {
			delete _p_log_11_04;
			_p_log_11_04 = nullptr;
		}
	}

	log4cpp::Appender* _appender;
	log4cpp::Category* _category;

	static Singleton_test_11_04* _p_log_11_04;
	static pthread_once_t _oncePthreadOnce;
};

Singleton_test_11_04* Singleton_test_11_04::_p_log_11_04 = nullptr;
pthread_once_t Singleton_test_11_04::_oncePthreadOnce = PTHREAD_ONCE_INIT;

void test_11_04() {
	Singleton_test_11_04::getInstance()->debug("The log is a debug message");
}

//
// Created by 李勃鋆 on 24-8-21.
//
#include "../week02.h"
#ifdef __linux__
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PropertyConfigurator.hh>
using namespace log4cpp;
#endif

void test_08_01() {
	Appender* appender1 = new OstreamAppender("console", &cout);
	PatternLayout* layout1 = new PatternLayout();
	layout1->setConversionPattern("%d %c [%p] %m%n");
	appender1->setLayout(layout1);

	Appender* appender2 = new FileAppender("default", "demo.log");
	PatternLayout* layout2 = new PatternLayout();
	layout2->setConversionPattern("%d %c [%p] %m%n");
	appender2->setLayout(layout2);

	Appender* appender3 = new RollingFileAppender("rolling", "test.log", 1024 * 1024, 4);
	PatternLayout* layout3 = new PatternLayout();
	layout3->setConversionPattern("%d %c [%p] %m%n");
	appender3->setLayout(layout3);

	Category& root = Category::getRoot();
	root.setPriority(Priority::DEBUG);
	root.addAppender(appender1);
	root.addAppender(appender2);

	Category& sub1 = Category::getInstance(string("sub1"));
	sub1.setPriority(Priority::INFO);
	sub1.addAppender(appender3);

	for (int i = 0; i < 32; i++) {
		// use of functions for logging messages
		root.error("root error");
		root.info("root info");
		sub1.error("sub1 error");
		sub1.warn("sub1 warn");

		// printf-style for logging variables
		root.warn("%d + %d == %s ?", 1, 1, "two");

		// use of streams for logging messages
		root << log4cpp::Priority::ERROR << "Streamed root error";
		root << log4cpp::Priority::INFO << "Streamed root info";
		sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
		sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

		// or this way:
		root.errorStream() << "Another streamed error";
	}
	Category::shutdown();
}

class Mylogger {
public:
	Mylogger(const Mylogger& log) = delete;

	Mylogger& operator=(const Mylogger& log) = delete;

	void warn(const std::string& data) const;

	void error(const std::string& data) const;

	void debug(const std::string& data) const;

	void info(const std::string& data) const;

	void fatal(const std::string& data) const;

	void crit(const std::string& data) const;

	friend void LogInfo(const std::string& buffer);

	friend void LogError(const std::string& buffer);

	friend void LogWarn(const std::string& buffer);

	friend void LogDebug(const std::string& buffer);

	friend void LogFatal(const std::string& buffer);

	friend void LogCrit(const std::string& buffer);

	static Mylogger* getInstance() {
#ifdef __linux__
		if (p_log == nullptr) {
			p_log = new Mylogger();
		}
#endif
		return p_log;
	}

	static void destroyInstance() {
#ifdef __linux__
		delete p_log;
		p_log = nullptr;
#endif
	}

private:
	Mylogger() {
#ifdef __linux__
		_appender = new log4cpp::OstreamAppender("console", &std::cout);
		log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
		layout->setConversionPattern("%d [%c] [%p] - %m%n");
		_appender->setLayout(layout);

		_category = &log4cpp::Category::getRoot();
		_category->addAppender(_appender);
		_category->setPriority(log4cpp::Priority::DEBUG); // 默认优先级设置为 DEBUG
#endif
	}

	~Mylogger() {
#ifdef __linux__
		log4cpp::Category::shutdown();
#endif
	}

	static void initSingleton() {
#ifdef __linux__
		p_log = new Mylogger();
#endif
	}

#ifdef __linux__
	log4cpp::Appender* _appender;
	log4cpp::Category* _category;
#endif
	static Mylogger* p_log;
};

#ifdef __linux__
Mylogger* Mylogger::p_log = nullptr;
#endif

// 日志记录方法实现
void Mylogger::warn(const std::string& data) const {
#ifdef __linux__
	_category->warn(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
#endif
}

void Mylogger::error(const std::string& data) const {
#ifdef __linux__
	_category->error(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
#endif
}

void Mylogger::debug(const std::string& data) const {
#ifdef __linux__
	_category->debug(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
#endif
}

void Mylogger::info(const std::string& data) const {
#ifdef __linux__
	_category->info(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
#endif
}

void Mylogger::fatal(const std::string& data) const {
#ifdef __linux__
	_category->fatal(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
#endif
}

void Mylogger::crit(const std::string& data) const {
#ifdef __linux__
	_category->crit(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
#endif
}

// Log functions
void LogInfo(const std::string& buffer) {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->info(buffer);
#endif
}

void LogError(const std::string& buffer) {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->error(buffer);
#endif
}

void LogWarn(const std::string& buffer) {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->warn(buffer);
#endif
}

void LogDebug(const std::string& buffer) {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->debug(buffer);
#endif
}

void LogFatal(const std::string& buffer) {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->fatal(buffer);
#endif
}

void LogCrit(const std::string& buffer) {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->crit(buffer);
#endif
}

void test_08_02() {
#ifdef __linux__
	const Mylogger* log = Mylogger::getInstance();
	log->info("The log is an info message");
	log->error("The log is an error message");
	log->fatal("The log is a fatal message");
	log->crit("The log is a crit message");
	log->warn("The log is a warn message");
	log->debug("The log is a debug message");
	Mylogger::destroyInstance();
#endif
}

void test_08_03() {
#ifdef __linux__
	LogInfo("The log is info message");
	LogError("The log is error message");
	LogWarn("The log is warn message");
	LogDebug("The log is debug message");
	LogFatal("The log is fatal message");
	LogCrit("The log is critical message");
	Mylogger::destroyInstance();
#endif
}

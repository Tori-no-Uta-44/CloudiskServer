//
// Created by 李勃鋆 on 24-8-20.
//
#include "../week02.h"

void test_08_01() {
	Appender* appender1 = new OstreamAppender("console", &cout);
	auto* layout1 = new PatternLayout();
	layout1->setConversionPattern("%d %c [%p] %m%n");
	appender1->setLayout(layout1);

	Appender* appender2 = new FileAppender("default", "demo.log");
	auto* layout2 = new PatternLayout();
	layout2->setConversionPattern("%d %c [%p] %m%n");
	appender2->setLayout(layout2);

	Appender* appender3 = new RollingFileAppender("rolling", "test.log", 1024 * 1024, 4);
	auto* layout3 = new PatternLayout();
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
		if (p_log == nullptr) {
			p_log = new Mylogger();
		}

		return p_log;
	}

	static void destroyInstance() {
		delete p_log;
		p_log = nullptr;
	}

private:
	Mylogger() {
		_appender = new log4cpp::OstreamAppender("console", &std::cout);
		auto* layout = new log4cpp::PatternLayout();
		layout->setConversionPattern("%d [%c] [%p] - %m%n");
		_appender->setLayout(layout);

		_category = &log4cpp::Category::getRoot();
		_category->addAppender(_appender);
		_category->setPriority(log4cpp::Priority::DEBUG); // 默认优先级设置为 DEBUG
	}

	~Mylogger() {
		log4cpp::Category::shutdown();
	}

	static void initSingleton() {
		p_log = new Mylogger();
	}


	log4cpp::Appender* _appender;
	log4cpp::Category* _category;

	static Mylogger* p_log;
};


Mylogger* Mylogger::p_log = nullptr;


// 日志记录方法实现
void Mylogger::warn(const std::string& data) const {
	_category->warn(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
}

void Mylogger::error(const std::string& data) const {
	_category->error(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
}

void Mylogger::debug(const std::string& data) const {
	_category->debug(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
}

void Mylogger::info(const std::string& data) const {
	_category->info(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
}

void Mylogger::fatal(const std::string& data) const {
	_category->fatal(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
}

void Mylogger::crit(const std::string& data) const {
	_category->crit(
		"File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
		std::to_string(__LINE__) + " - " + data);
}

// Log functions
void LogInfo(const std::string& buffer) {
	const Mylogger* log = Mylogger::getInstance();
	log->info(buffer);
}

void LogError(const std::string& buffer) {
	const Mylogger* log = Mylogger::getInstance();
	log->error(buffer);
}

void LogWarn(const std::string& buffer) {
	const Mylogger* log = Mylogger::getInstance();
	log->warn(buffer);
}

void LogDebug(const std::string& buffer) {
	const Mylogger* log = Mylogger::getInstance();
	log->debug(buffer);
}

void LogFatal(const std::string& buffer) {
	const Mylogger* log = Mylogger::getInstance();
	log->fatal(buffer);
}

void LogCrit(const std::string& buffer) {
	const Mylogger* log = Mylogger::getInstance();
	log->crit(buffer);
}

void test_08_02() {
	const Mylogger* log = Mylogger::getInstance();
	log->info("The log is an info message");
	log->error("The log is an error message");
	log->fatal("The log is a fatal message");
	log->crit("The log is a crit message");
	log->warn("The log is a warn message");
	log->debug("The log is a debug message");
	Mylogger::destroyInstance();
}

void test_08_03() {
	LogInfo("The log is info message");
	LogError("The log is error message");
	LogWarn("The log is warn message");
	LogDebug("The log is debug message");
	LogFatal("The log is fatal message");
	LogCrit("The log is critical message");
	Mylogger::destroyInstance();
}

class Point_test_08_04;

class Line_test_08_04 {
public:
	double distance(Point_test_08_04 p1, Point_test_08_04 p2);
};

class Point_test_08_04 {
private:
	double _ix = 0.0;
	double _iy = 0.0;

public:
	friend double Line_test_08_04::distance(Point_test_08_04 p1, Point_test_08_04 p2);

	Point_test_08_04() = default;

	Point_test_08_04(double ix, double iy): _ix(ix), _iy(iy) {
	}
};

double Line_test_08_04::distance(Point_test_08_04 p1, Point_test_08_04 p2) {
	const double x = p1._ix - p2._ix;
	const double y = p1._iy - p2._iy;
	return sqrt(x * x + y * y);
}

void test_08_04() {
	Point_test_08_04 p1(1.4, 3.3);
	Point_test_08_04 p2(4.4, 1.6);
	Line_test_08_04 l;
	std::cout << l.distance(p1, p2) << endl;
}

class Log_demo_08_01 {
public:

};

void demo_08_01() {

}
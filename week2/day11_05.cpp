//
// Created by 李勃鋆 on 24-8-23.
//

#include "../week02.h"

class Singleton_test_11_05 {
public:
    Singleton_test_11_05(const Singleton_test_11_05& log) = delete;
    Singleton_test_11_05& operator=(const Singleton_test_11_05& log) = delete;

    void debug(const std::string& data) const {
        _category->debug(
            "File: " + std::string(__FILE__) + ", Function: " + std::string(__func__) + ", Line: " +
            std::to_string(__LINE__) + " - " + data);
    }

    static Singleton_test_11_05* getInstance() {
        std::call_once(_once_flag, []() {
            _p_log_11_05 = new Singleton_test_11_05();
            atexit(destroyInstance); // 注册析构函数在程序结束时自动调用
        });

        return _p_log_11_05;
    }

private:
    Singleton_test_11_05() {
        _appender = new log4cpp::OstreamAppender("console", &std::cout);
        auto* layout = new log4cpp::PatternLayout();
        layout->setConversionPattern("%d [%c] [%p] - %m%n");
        _appender->setLayout(layout);

        _category = &log4cpp::Category::getRoot();
        _category->addAppender(_appender);
        _category->setPriority(log4cpp::Priority::DEBUG); // 默认优先级设置为 DEBUG
    }

    ~Singleton_test_11_05() {
        log4cpp::Category::shutdown();
    }

    static void destroyInstance() {
        if (_p_log_11_05 != nullptr) {
            delete _p_log_11_05;
            _p_log_11_05 = nullptr;
        }
    }

    log4cpp::Appender* _appender;
    log4cpp::Category* _category;

    static Singleton_test_11_05* _p_log_11_05;
    static std::once_flag _once_flag; // 用于 std::call_once 的 flag
};

Singleton_test_11_05* Singleton_test_11_05::_p_log_11_05 = nullptr;
std::once_flag Singleton_test_11_05::_once_flag;

void test_11_05() {
    Singleton_test_11_05::getInstance()->debug("The log is a debug message");
}
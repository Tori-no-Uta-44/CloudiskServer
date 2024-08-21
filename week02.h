//
// Created by 李勃鋆 on 24-8-19.
//

#ifndef WEEK02_H
#define WEEK02_H
#include "week01.h"
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
#endif
using namespace log4cpp;

void test_07_01();

void test_07_02();

void test_07_03();

void test_07_04();

void test_08_01();

void test_08_02();

void test_08_03();

void test_08_04();

#endif //WEEK02_H

//
// Created by 李勃鋆 on 24-8-13.
//

#ifndef DAY01_H
#define DAY01_H

#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <cctype>
#include <chrono>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <mutex>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <csignal>
using namespace std;

void test_01_01();

void test_01_02();

void test_02_01();

void test_02_02();

void demo_01_01();

void demo_01_02();

void demo_02_01();

void test04_01();

void test04_02();

void test_05_01();

void test_05_02();

void test_05_03();

void test_05_04();

void test_05_05();

void test_05_06();

void test_06_01();

void test_06_02();

void test_06_03();

void test_06_04();

char *sCopy(char *dest, const char *src);

char *sNCopy(char *dest, const char *src, int count);

long sLen(const char *s);

char *sCat(char *dest, const char *src);

char *sNCat(char *dest, const char *src, int count);

int sCmp(const char *s1, const char *s2);

int sNCmp(const char *s1, const char *s2, int count);

int adList_test();

int AdMatrix_test();

int BFS_test();

int ConnectedComponents_test();

int countingSort_test();

int DAG_test();

int DFS_test();

void prefixSum1();

void prefixSum2();

int radixSort_test();

void WF_test01();

void WF_test02_02();

void WF_test02_04();

void WF_test03_1();

void WF_test03_2();

int test_wfrest();

void ossTest();

int test_rabbitmq();
#endif //DAY01_H

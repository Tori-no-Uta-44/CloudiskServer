//
// Created by 李勃鋆 on 24-8-13.
//

#ifndef DAY01_H
#define DAY01_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <cctype>
#include <sstream>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <mutex>
#include <regex>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <deque>
#include <list>
#include <random>
#include <array>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <queue>
#include <stack>
#include <functional>
#include <climits>
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
#endif //DAY01_H

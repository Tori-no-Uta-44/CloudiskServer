//
// Created by 李勃鋆 on 24-8-13.
//

#include "../week01.h"

void f2(int &x, int &y) {
    int z = x;
    x = y;
    y = z;
}

void f3(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}

void test_02_01() {
    int x, y;
    x = 10;
    y = 26;
    std::cout << "x,y:" << x << "," << y << std::endl;
    f2(x, y);
    std::cout << "x,y:" << x << "," << y << std::endl;
    f3(&x, &y);
    std::cout << "x,y:" << x << "," << y << std::endl;
    x++;
    y--;
    f2(y, x);
    std::cout << "x,y:" << x << "," << y << std::endl;
}

namespace my_namespace {
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, int b) {
        return a + b;
    }

    double add(int a, double b = 44.0) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }
}

void test_02_02() {
    using namespace my_namespace;
    std::cout << "add(1, 2) = " << add(1, 2) << std::endl;
    std::cout << "add(1.0, 2) = " << add(1.0, 2) << std::endl;
    std::cout << "add(1, 2.0) = " << add(1, 2.0) << std::endl;
    std::cout << "add(2) = " << add(2) << std::endl;
    std::cout << "add(1, 2, 3) = " << add(1, 2, 3) << std::endl;
}

int gNum = 1;
const int gcNum = 20;

void demo_02_01() {
    //内存布局
    const char *ps = "aa";
    const int cNum = 0;//栈
    static int sNum = 1;//全局/静态
    char arr0[6] = {'a', 'b', 'c', 'd', 'e', '\0'};//栈
    char arr1[] = "elysian";//栈
    std::cout << "&arr1--" << &arr1 << std::endl;
    std::cout << "&arr0--" << &arr0 << std::endl;
    std::cout << "&cNum--" << &cNum << std::endl;
    std::cout << "arr0:" << arr0 << std::endl;
    std::cout << "arr1:" << arr1 << std::endl;
    char *pstr = new char[std::strlen(ps) + 1];
    int *p2 = new int(10);
    std::strcpy(pstr, ps);
    std::cout << "pstr:" << pstr << std::endl;
    const char *p = new char[6]{'f', 'g', 'h', 'i', 'j', '\0'};
    std::cout << "&pstr--" << &pstr << std::endl;
    std::cout << "&p2--" << p2 << std::endl;
    std::cout << "&p--" << p << std::endl;
    std::cout << "&sNum--" << &sNum << std::endl;
    std::cout << "&gNum--" << &gNum << std::endl;
    std::cout << "p:" << p << std::endl;
    std::cout << static_cast<void *>(const_cast<char *>(pstr)) << std::endl;
    std::cout << "&gcNum--" << &gcNum << std::endl;
    delete[] pstr;
    delete p2;
    delete[] p;
    std::cout<<"---"<<std::endl;

}

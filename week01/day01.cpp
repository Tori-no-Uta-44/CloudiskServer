//
// Created by 李勃鋆 on 24-8-13.
//

#include "../week01.h"

int foo(int x, int y) {
    if (x <= 0 || y <= 0) {
        return 1;
    }
    return 3 * foo(x - 1, y / 2);
}

void test_01_01() {
    std::cout << foo(3, 5) << std::endl;
    int x;
    std::cin >> x;
    if (x++ > 5) {
        std::cout << x << std::endl;
    }
    std::cout << x-- << std::endl;
    int a[5] = {1, 2, 3, 4, 5};
    int *p = reinterpret_cast<int *>(&a + 1);
    std::cout << *(a + 1) << "\t" << *(p - 1) << std::endl;
}

void test_01_02() {
    const char *p = "hello world";
    char *arr = new char[strlen(p) + 1];
    strcpy(arr, p);
    std::cout << arr << std::endl;
    delete[] arr;
    arr = nullptr;
}

void demo_01_01() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << arr << std::endl;
    std::cout << &arr << std::endl;
    std::cout << arr + 1 << std::endl;
    std::cout << &arr + 1 << std::endl;
}
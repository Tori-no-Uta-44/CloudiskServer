cmake_minimum_required(VERSION 3.22)
project(cpp01_02)

set(CMAKE_CXX_STANDARD 17)

# 找到 PkgConfig
find_package(PkgConfig REQUIRED)

# 查找 log4cpp 库
pkg_check_modules(LOG4CPP REQUIRED log4cpp)

# 包含 log4cpp 头文件路径
include_directories(${LOG4CPP_INCLUDE_DIRS})

# 链接 log4cpp 库路径
link_directories(${LOG4CPP_LIBRARY_DIRS})

# 添加可执行文件
add_executable(cpp01_02
        main.cpp
        week1/day01.cpp
        week01.h
        week1/day02.cpp
        week1/day03_04.cpp
        func.h
        week1/day05.cpp
        week1/day06.cpp
        week2/day07.cpp
        week02.h
        week2/day08.cpp
        week2/day09.cpp
        week2/day10.cpp
        week2/day11_02.cpp
        week2/day11_01.cpp
        week2/day11_03.cpp
        week2/day11_04.cpp
        week2/day11_05.cpp
        week2/day11_06.cpp
        week2/day11_07.cpp
        week2/day12_01.cpp
        week2/day12_02.cpp
        week2/day11_08.cpp
        week2/day12_03.cpp
        week03.h
        week3/day13_01.cpp
        week3/day13_02.cpp
        week3/tinyxml2.cpp
        week3/day13_03.cpp
        week3/day14_01.cpp
        week3/day14_02.cpp
        week3/day14_03.cpp
        week3/day15_01.cpp
        week3/day16_01.cpp
        week3/day16_02.cpp
        week3/day17_01.cpp
        week3/day17_02.cpp
)

# 为可执行文件启用 ASan
target_compile_options(cpp01_02 PRIVATE -fsanitize=address -g)
target_link_options(cpp01_02 PRIVATE -fsanitize=address)

# 链接 log4cpp 库到可执行文件
target_link_libraries(cpp01_02 ${LOG4CPP_LIBRARIES})
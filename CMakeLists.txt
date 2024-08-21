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
        week01/day01.cpp
        week01.h
        week01/day02.cpp
        week01/day03_04.cpp
        func.h
        week01/day05.cpp
        week01/day06.cpp
        week2/day07.cpp
        week02.h
        week2/day08.cpp
)

# 为可执行文件启用 ASan
target_compile_options(cpp01_02 PRIVATE -fsanitize=address -g)
target_link_options(cpp01_02 PRIVATE -fsanitize=address)

# 链接 log4cpp 库到可执行文件
target_link_libraries(cpp01_02 ${LOG4CPP_LIBRARIES})

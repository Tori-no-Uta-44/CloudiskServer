cmake_minimum_required(VERSION 3.22)
project(cpp01_02)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    # 仅在 Linux 上查找 PkgConfig 和 log4cpp
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LOG4CPP REQUIRED log4cpp)
    include_directories(${LOG4CPP_INCLUDE_DIRS})
    link_directories(${LOG4CPP_LIBRARY_DIRS})
endif()

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
        week2/log.cpp
)

# 为可执行文件启用 ASan
if (UNIX)
    target_compile_options(cpp01_02 PRIVATE -fsanitize=address -g)
    target_link_options(cpp01_02 PRIVATE -fsanitize=address)
endif()

if (UNIX)
    # 仅在 Linux 上链接 log4cpp 库到可执行文件
    target_link_libraries(cpp01_02 ${LOG4CPP_LIBRARIES})
endif()

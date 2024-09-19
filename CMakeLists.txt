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
        week1/day1.cpp
        week01.h
        week1/day2.cpp
        week1/day3+4.cpp
        func.h
        week1/day5.cpp
        week1/day6.cpp
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
        week3/strings.cpp
        week4/day18_1.cpp
        week04.h
        week4/day20_1.cpp
        week4/day21_1.cpp
        week0/countingSort.cpp
        week0/prefixSum.cpp
        week4/day22_1.cpp
        week4/day23_1.cpp
        week0/radixSort.cpp
        week0/AdjacencyList.cpp
        week0/AdjacencyMatrix.cpp
        week0/BFS.cpp
        week0/ConnectedComponents.cpp
        week0/DFS.cpp
        week0/DAG.cpp
        week5.h
        week5/day25_1.cpp
        week4/day24_01.cpp
        week5/day27.cpp
        week5/day28_1.cpp
        week5/day29_1.cpp
        week5/day30_1.cpp
        week5/STaskQueue.cpp
        week5/STaskQueue.h
        week5/SThreadPoll.cpp
        week5/SThreadPoll.h
        week5/Task.h
        week5/STaskQueue.cpp
        week5/AbstractShape.h
        week5/AbstractColor.h
        week5/Shape.cpp
        week5/Shape.h
        week5/Color.cpp
        week5/Color.h
        week5/Tasks.cpp
        week5/Tasks.h
        week6/ReactorV2/Acceptor.h
        week6/ReactorV2/Acceptor.cpp
        week6/ReactorV2/InetAddress.cpp
        week6/ReactorV2/Socket.cpp
        week6/ReactorV2/TcpConnection.cpp
        week6/ReactorV2/SocketIO.cpp
        week6.h
        week6/ReactorV2/EventLoop.cpp
        week6/ReactorV2/EventLoop.h
        week6/day33_1.cpp
)

# 为可执行文件启用 ASan
target_compile_options(cpp01_02 PRIVATE -fsanitize=address -g)
target_link_options(cpp01_02 PRIVATE -fsanitize=address)

# 链接 log4cpp 库到可执行文件
target_link_libraries(cpp01_02 ${LOG4CPP_LIBRARIES})

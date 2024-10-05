cmake_minimum_required(VERSION 3.22)
project(cpp01_02)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)

# 找到 PkgConfig
find_package(PkgConfig REQUIRED)

# 使用 PkgConfig 查找库
pkg_check_modules(HIREDIS REQUIRED hiredis)
pkg_check_modules(REDIS_PLUS_PLUS REQUIRED redis++)
pkg_check_modules(LOG4CPP REQUIRED log4cpp)
pkg_check_modules(OPENSSL REQUIRED openssl)

# 手动指定 workflow 库的头文件和库路径
include_directories(/usr/local/include/workflow)
link_directories(/usr/local/lib)

# 包含 hiredis、redis++、log4cpp 和 OpenSSL 的头文件
include_directories(
        ${HIREDIS_INCLUDE_DIRS}
        ${REDIS_PLUS_PLUS_INCLUDE_DIRS}
        ${LOG4CPP_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIRS}
)

# 链接库路径
link_directories(
        ${HIREDIS_LIBRARY_DIRS}
        ${REDIS_PLUS_PLUS_LIBRARY_DIRS}
        ${LOG4CPP_LIBRARY_DIRS}
        ${OPENSSL_LIBRARY_DIRS}
)

# 添加可执行文件并列出所有源文件
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
        week5/TaskQueue.cpp
        week5/TaskQueue.h
        week5/SThreadPoll.cpp
        week5/SThreadPoll.h
        week5/Task.h
        week5/TaskQueue.cpp
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
        week6/ReactorV4/Acceptor.h
        week6/ReactorV4/Acceptor.cpp
        week6/ReactorV4/InetAddress.cpp
        week6/ReactorV4/Socket.cpp
        week6/ReactorV4/TcpConnection.cpp
        week6/ReactorV4/SocketIO.cpp
        week6/ReactorV4/EventLoop.cpp
        week6/ReactorV4/EventLoop.h
        week6/ReactorV4/TaskQueue.h
        week6/ReactorV4/TaskQueue.cpp
        week6/ReactorV4/ThreadPool.h
        week6/ReactorV4/ThreadPool.cpp
        week6/ReactorV4/TCpServer.cpp
        week6/ReactorV4/TCpServer.h
        week6/day34_1.cpp
        week6/ReactorV4/AbstractColor.h
        week6/ReactorV4/AbstractShape.h
        week6/ReactorV4/Color.h
        week6/ReactorV4/Color.cpp
        week6/ReactorV4/Shape.h
        week6/ReactorV4/Shape.cpp
        week6/ReactorV4/Tasks.h
        week6/ReactorV4/Tasks.cpp
        week6/ReactorV5/Acceptor.h
        week6/ReactorV5/Acceptor.cpp
        week6/ReactorV5/InetAddress.cpp
        week6/ReactorV5/Socket.cpp
        week6/ReactorV5/TcpConnection.cpp
        week6/ReactorV5/SocketIO.cpp
        week6/ReactorV5/EventLoop.cpp
        week6/ReactorV5/EventLoop.h
        week6/ReactorV5/TaskQueue.h
        week6/ReactorV5/TaskQueue.cpp
        week6/ReactorV5/ThreadPool.h
        week6/ReactorV5/ThreadPool.cpp
        week6/ReactorV5/TCpServer.cpp
        week6/ReactorV5/TCpServer.h
        week6/ReactorV5/AbstractColor.h
        week6/ReactorV5/AbstractShape.h
        week6/ReactorV5/Color.h
        week6/ReactorV5/Color.cpp
        week6/ReactorV5/Shape.h
        week6/ReactorV5/Shape.cpp
        week6/ReactorV5/Tasks.h
        week6/ReactorV5/Tasks.cpp
        week6/ReactorV5/EchoServer.cpp
        week6/ReactorV5/EchoServer.h
        week6/ReactorV5/Timerfd.cpp
        week6/ReactorV5/Timerfd.h
        week6/Test_redis.cpp
        week6/Test_workflow.cpp
)

# 为可执行文件启用 AddressSanitizer
target_compile_options(cpp01_02 PRIVATE -fsanitize=address -g)
target_link_options(cpp01_02 PRIVATE -fsanitize=address)

# 链接库到可执行文件
target_link_libraries(cpp01_02
        ${HIREDIS_LIBRARIES}
        ${REDIS_PLUS_PLUS_LIBRARIES}
        ${LOG4CPP_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        workflow  # 手动链接 workflow 库
        ${LIBRT}
)

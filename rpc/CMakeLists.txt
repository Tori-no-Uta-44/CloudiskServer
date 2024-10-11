# rpc/CMakeLists.txt
add_library(rpc_library
        client.pb_skeleton.cc
        server.pb_skeleton.cc
        signin.pb.cc
)

# 包含根目录中的 include 和库路径设置
target_include_directories(rpc_library PUBLIC ${CMAKE_SOURCE_DIR})
target_link_directories(rpc_library PUBLIC ${CMAKE_BINARY_DIR})

# 链接公共库
target_link_libraries(rpc_library
        ${HIREDIS_LIBRARIES}
        ${REDIS_PLUS_PLUS_LIBRARIES}
        ${LOG4CPP_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        workflow  # 手动链接 workflow 库
        wfrest
        ${LIBRT}
        rt
        ${OSS_SDK_LIBRARY}
        ${CURL_LIBRARY}
        ${CRYPTO_LIBRARY}
        Threads::Threads
        ${SIMPLE_AMQP_CLIENT_LIBRARY}
        rt
        lz4
        snappy
        crypt
        ${SRPC_LIBRARY}
)

# 可执行文件

add_executable(rpc_server server.pb_skeleton.cc)
target_link_libraries(rpc_server rpc_library)
add_executable(rpc_client client.pb_skeleton.cc)
target_link_libraries(rpc_client rpc_library)
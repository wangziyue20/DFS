add_library(master
    global_node_manager.cpp
    nodeManager.cpp
    )

target_include_directories(master
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/include/master
    )


add_executable(master_server
    heartbeat_server.cpp
    master_server.cpp
    )

target_compile_definitions(master_server PRIVATE CROW_USE_BOOST)

target_include_directories(master_server
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/include/master
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    )

target_link_libraries(master_server
    PUBLIC
    master
    "/usr/local/lib/libmuduo_net.a" 
    "/usr/local/lib/libmuduo_base.a"
)
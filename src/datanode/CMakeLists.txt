# data_main可执行程序
# node_selector编译成库
# local_node_info编译成库


add_library(local_node_info
    local_node_info.cpp
    )

target_include_directories(local_node_info 
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/datanode
    )  
# ***************************************
add_executable(datanode_main
    heartbeat_client.cpp
    datanode_main.cpp
    )

target_compile_definitions(datanode_main PUBLIC CROW_USE_BOOST)

target_include_directories(datanode_main
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/include/api
    )

target_link_libraries(datanode_main 
    PUBLIC
    local_node_info
    upload_manager
    download_manager
    "/usr/local/lib/libmuduo_net.a" 
    "/usr/local/lib/libmuduo_base.a"
)
# ***************************************
add_library(selector
    node_selector.cpp
    )
    
target_compile_definitions(selector PUBLIC CROW_USE_BOOST)

target_include_directories(selector 
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    )

target_link_libraries(selector
    PUBLIC
    curl
    )

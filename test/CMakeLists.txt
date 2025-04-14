add_executable(server 
    heart_try_server.cpp
)

target_include_directories(server
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/include/master
    )
 
target_link_libraries(server 
    master
    "/usr/local/lib/libmuduo_net.a" 
    "/usr/local/lib/libmuduo_base.a"
)

add_executable(client
    heart_try_client.cpp
)

target_include_directories(client
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/include/master
    )

target_link_libraries(client 
    PUBLIC
    datanode
    "/usr/local/lib/libmuduo_net.a" 
    "/usr/local/lib/libmuduo_base.a"
)
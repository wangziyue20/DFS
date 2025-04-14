find_library(HIREDIS_LIB hiredis REQUIRED)

set(SOURCES
    # main.cpp
    file_manager.cpp
    mysql_client.cpp
    redis_client.cpp
)

# 构建可执行文件
add_library(storage ${SOURCES})

target_include_directories(storage 
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/storage)

# 链接 MySQL client 库
target_link_libraries(storage mysqlclient ${HIREDIS_LIB})
# upload download可执行程序
# delete 可执行程序
# upload_manager.cpp download_manager.cpp编译成库
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(upload
    upload_server.cpp
)

target_compile_definitions(upload PUBLIC CROW_USE_BOOST)
# add_definitions(-DCROW_ENABLE_MULTIPART)

# 包含 storage 目录
target_include_directories(upload
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    ${CMAKE_SOURCE_DIR}/third_party/cpp-httplib
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/storage
    ${CMAKE_SOURCE_DIR}/include/api
    ${CMAKE_SOURCE_DIR}/include/datanode
    )

# 链接 storage 库 和 muduo
target_link_libraries(upload
    PUBLIC
    OpenSSL::Crypto
    common
    selector
    storage
    uuid
    master
)
# *************************************
add_executable(download
    download_server.cpp
)

target_compile_definitions(download PUBLIC CROW_USE_BOOST)
# add_definitions(-DCROW_ENABLE_MULTIPART)

# 包含 storage 目录
target_include_directories(download
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    ${CMAKE_SOURCE_DIR}/third_party/cpp-httplib
    ${CMAKE_SOURCE_DIR}/include/storage
    ${CMAKE_SOURCE_DIR}/include/api
    ${CMAKE_SOURCE_DIR}/include/datanode
    )

# 链接 storage 库 和 muduo
target_link_libraries(download
    PUBLIC
    selector
    storage
    uuid
    master
)
# //*********************************************
add_library(upload_manager
    upload_manager.cpp
)

target_compile_definitions(upload_manager PUBLIC CROW_USE_BOOST)
# add_definitions(-DCROW_ENABLE_MULTIPART)

# 包含 storage 目录
target_include_directories(upload_manager
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    ${CMAKE_SOURCE_DIR}/include/storage
    ${CMAKE_SOURCE_DIR}/include/api
    ${CMAKE_SOURCE_DIR}/include/datanode
    )

# 链接 storage 库 和 muduo
target_link_libraries(upload_manager
    PUBLIC
    local_node_info
    selector
    storage
    uuid
    master
)
# //*********************************************
add_library(download_manager
    download_manager.cpp
)

target_compile_definitions(download_manager PUBLIC CROW_USE_BOOST)
# add_definitions(-DCROW_ENABLE_MULTIPART)

# 包含 storage 目录
target_include_directories(download_manager
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    ${CMAKE_SOURCE_DIR}/include/storage
    ${CMAKE_SOURCE_DIR}/include/api
    ${CMAKE_SOURCE_DIR}/include/datanode
    ${CMAKE_SOURCE_DIR}/include/common
    )

# 链接 storage 库 和 muduo
target_link_libraries(download_manager
    PUBLIC
    OpenSSL::Crypto
    common
    selector
    storage
    uuid
    master
)

# *************************************
add_executable(delete
    delete_server.cpp
)

target_compile_definitions(delete PUBLIC CROW_USE_BOOST)
# add_definitions(-DCROW_ENABLE_MULTIPART)

# 包含 storage 目录
target_include_directories(delete
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/third_party/Crow/include
    ${CMAKE_SOURCE_DIR}/third_party/cpp-httplib
    ${CMAKE_SOURCE_DIR}/include/storage
    ${CMAKE_SOURCE_DIR}/include/api
    ${CMAKE_SOURCE_DIR}/include/datanode
    )

# 链接 storage 库 和 muduo
target_link_libraries(delete
    PUBLIC
    storage
)
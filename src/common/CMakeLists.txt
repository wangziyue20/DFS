find_package(OpenSSL REQUIRED)

set(SOURCES
    calculateSHA.cpp
)

# 构建可执行文件
add_library(common ${SOURCES})

target_include_directories(common
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include/common
    )

target_link_libraries(common 
    PUBLIC 
    OpenSSL::Crypto
    )
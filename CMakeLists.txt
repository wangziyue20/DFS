cmake_minimum_required(VERSION 3.10)
project(distributed_file_system)

set(CMAKE_CXX_STANDARD 17)

# 设置可执行文件输出路径（可选）
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
# add_subdirectory(test)
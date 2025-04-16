find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(common)
add_subdirectory(storage)
add_subdirectory(api)
add_subdirectory(datanode)
add_subdirectory(master)
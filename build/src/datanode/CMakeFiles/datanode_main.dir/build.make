# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/book/Desktop/chat/proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/book/Desktop/chat/proj/build

# Include any dependencies generated for this target.
include src/datanode/CMakeFiles/datanode_main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/datanode/CMakeFiles/datanode_main.dir/compiler_depend.make

# Include the progress variables for this target.
include src/datanode/CMakeFiles/datanode_main.dir/progress.make

# Include the compile flags for this target's objects.
include src/datanode/CMakeFiles/datanode_main.dir/flags.make

src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o: src/datanode/CMakeFiles/datanode_main.dir/flags.make
src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o: /home/book/Desktop/chat/proj/src/datanode/heartbeat_client.cpp
src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o: src/datanode/CMakeFiles/datanode_main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/Desktop/chat/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o"
	cd /home/book/Desktop/chat/proj/build/src/datanode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o -MF CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o.d -o CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o -c /home/book/Desktop/chat/proj/src/datanode/heartbeat_client.cpp

src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datanode_main.dir/heartbeat_client.cpp.i"
	cd /home/book/Desktop/chat/proj/build/src/datanode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/book/Desktop/chat/proj/src/datanode/heartbeat_client.cpp > CMakeFiles/datanode_main.dir/heartbeat_client.cpp.i

src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datanode_main.dir/heartbeat_client.cpp.s"
	cd /home/book/Desktop/chat/proj/build/src/datanode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/book/Desktop/chat/proj/src/datanode/heartbeat_client.cpp -o CMakeFiles/datanode_main.dir/heartbeat_client.cpp.s

src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.o: src/datanode/CMakeFiles/datanode_main.dir/flags.make
src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.o: /home/book/Desktop/chat/proj/src/datanode/datanode_main.cpp
src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.o: src/datanode/CMakeFiles/datanode_main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/Desktop/chat/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.o"
	cd /home/book/Desktop/chat/proj/build/src/datanode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.o -MF CMakeFiles/datanode_main.dir/datanode_main.cpp.o.d -o CMakeFiles/datanode_main.dir/datanode_main.cpp.o -c /home/book/Desktop/chat/proj/src/datanode/datanode_main.cpp

src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datanode_main.dir/datanode_main.cpp.i"
	cd /home/book/Desktop/chat/proj/build/src/datanode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/book/Desktop/chat/proj/src/datanode/datanode_main.cpp > CMakeFiles/datanode_main.dir/datanode_main.cpp.i

src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datanode_main.dir/datanode_main.cpp.s"
	cd /home/book/Desktop/chat/proj/build/src/datanode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/book/Desktop/chat/proj/src/datanode/datanode_main.cpp -o CMakeFiles/datanode_main.dir/datanode_main.cpp.s

# Object files for target datanode_main
datanode_main_OBJECTS = \
"CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o" \
"CMakeFiles/datanode_main.dir/datanode_main.cpp.o"

# External object files for target datanode_main
datanode_main_EXTERNAL_OBJECTS =

src/datanode/datanode_main: src/datanode/CMakeFiles/datanode_main.dir/heartbeat_client.cpp.o
src/datanode/datanode_main: src/datanode/CMakeFiles/datanode_main.dir/datanode_main.cpp.o
src/datanode/datanode_main: src/datanode/CMakeFiles/datanode_main.dir/build.make
src/datanode/datanode_main: src/datanode/liblocal_node_info.a
src/datanode/datanode_main: src/api/libupload_manager.a
src/datanode/datanode_main: src/api/libdownload_manager.a
src/datanode/datanode_main: /usr/local/lib/libmuduo_net.a
src/datanode/datanode_main: /usr/local/lib/libmuduo_base.a
src/datanode/datanode_main: src/datanode/liblocal_node_info.a
src/datanode/datanode_main: src/datanode/libselector.a
src/datanode/datanode_main: src/storage/libstorage.a
src/datanode/datanode_main: /usr/local/lib/libhiredis.so
src/datanode/datanode_main: src/master/libmaster.a
src/datanode/datanode_main: src/datanode/CMakeFiles/datanode_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/book/Desktop/chat/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable datanode_main"
	cd /home/book/Desktop/chat/proj/build/src/datanode && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/datanode_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/datanode/CMakeFiles/datanode_main.dir/build: src/datanode/datanode_main
.PHONY : src/datanode/CMakeFiles/datanode_main.dir/build

src/datanode/CMakeFiles/datanode_main.dir/clean:
	cd /home/book/Desktop/chat/proj/build/src/datanode && $(CMAKE_COMMAND) -P CMakeFiles/datanode_main.dir/cmake_clean.cmake
.PHONY : src/datanode/CMakeFiles/datanode_main.dir/clean

src/datanode/CMakeFiles/datanode_main.dir/depend:
	cd /home/book/Desktop/chat/proj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/book/Desktop/chat/proj /home/book/Desktop/chat/proj/src/datanode /home/book/Desktop/chat/proj/build /home/book/Desktop/chat/proj/build/src/datanode /home/book/Desktop/chat/proj/build/src/datanode/CMakeFiles/datanode_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/datanode/CMakeFiles/datanode_main.dir/depend


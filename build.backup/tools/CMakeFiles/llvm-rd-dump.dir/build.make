# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/tau/dg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/tau/dg/build

# Include any dependencies generated for this target.
include tools/CMakeFiles/llvm-rd-dump.dir/depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/llvm-rd-dump.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/llvm-rd-dump.dir/flags.make

tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o: tools/CMakeFiles/llvm-rd-dump.dir/flags.make
tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o: ../tools/llvm-rd-dump.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/tau/dg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o"
	cd /home/david/tau/dg/build/tools && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o -c /home/david/tau/dg/tools/llvm-rd-dump.cpp

tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.i"
	cd /home/david/tau/dg/build/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/tau/dg/tools/llvm-rd-dump.cpp > CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.i

tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.s"
	cd /home/david/tau/dg/build/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/tau/dg/tools/llvm-rd-dump.cpp -o CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.s

tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.requires:

.PHONY : tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.requires

tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.provides: tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.requires
	$(MAKE) -f tools/CMakeFiles/llvm-rd-dump.dir/build.make tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.provides.build
.PHONY : tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.provides

tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.provides.build: tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o


# Object files for target llvm-rd-dump
llvm__rd__dump_OBJECTS = \
"CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o"

# External object files for target llvm-rd-dump
llvm__rd__dump_EXTERNAL_OBJECTS =

tools/llvm-rd-dump: tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o
tools/llvm-rd-dump: tools/CMakeFiles/llvm-rd-dump.dir/build.make
tools/llvm-rd-dump: src/libLLVMdg.so
tools/llvm-rd-dump: src/libLLVMpta.so
tools/llvm-rd-dump: src/libPTA.so
tools/llvm-rd-dump: src/libRD.so
tools/llvm-rd-dump: tools/CMakeFiles/llvm-rd-dump.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/tau/dg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable llvm-rd-dump"
	cd /home/david/tau/dg/build/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/llvm-rd-dump.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/llvm-rd-dump.dir/build: tools/llvm-rd-dump

.PHONY : tools/CMakeFiles/llvm-rd-dump.dir/build

tools/CMakeFiles/llvm-rd-dump.dir/requires: tools/CMakeFiles/llvm-rd-dump.dir/llvm-rd-dump.cpp.o.requires

.PHONY : tools/CMakeFiles/llvm-rd-dump.dir/requires

tools/CMakeFiles/llvm-rd-dump.dir/clean:
	cd /home/david/tau/dg/build/tools && $(CMAKE_COMMAND) -P CMakeFiles/llvm-rd-dump.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/llvm-rd-dump.dir/clean

tools/CMakeFiles/llvm-rd-dump.dir/depend:
	cd /home/david/tau/dg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/tau/dg /home/david/tau/dg/tools /home/david/tau/dg/build /home/david/tau/dg/build/tools /home/david/tau/dg/build/tools/CMakeFiles/llvm-rd-dump.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/llvm-rd-dump.dir/depend


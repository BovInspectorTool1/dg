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
include tests/CMakeFiles/data-flow-test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/data-flow-test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/data-flow-test.dir/flags.make

tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o: tests/CMakeFiles/data-flow-test.dir/flags.make
tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o: ../tests/data-flow-test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/tau/dg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o"
	cd /home/david/tau/dg/build/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o -c /home/david/tau/dg/tests/data-flow-test.cpp

tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/data-flow-test.dir/data-flow-test.cpp.i"
	cd /home/david/tau/dg/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/tau/dg/tests/data-flow-test.cpp > CMakeFiles/data-flow-test.dir/data-flow-test.cpp.i

tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/data-flow-test.dir/data-flow-test.cpp.s"
	cd /home/david/tau/dg/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/tau/dg/tests/data-flow-test.cpp -o CMakeFiles/data-flow-test.dir/data-flow-test.cpp.s

tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.requires:

.PHONY : tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.requires

tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.provides: tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/data-flow-test.dir/build.make tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.provides.build
.PHONY : tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.provides

tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.provides.build: tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o


# Object files for target data-flow-test
data__flow__test_OBJECTS = \
"CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o"

# External object files for target data-flow-test
data__flow__test_EXTERNAL_OBJECTS =

tests/data-flow-test: tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o
tests/data-flow-test: tests/CMakeFiles/data-flow-test.dir/build.make
tests/data-flow-test: tests/CMakeFiles/data-flow-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/tau/dg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable data-flow-test"
	cd /home/david/tau/dg/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data-flow-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/data-flow-test.dir/build: tests/data-flow-test

.PHONY : tests/CMakeFiles/data-flow-test.dir/build

tests/CMakeFiles/data-flow-test.dir/requires: tests/CMakeFiles/data-flow-test.dir/data-flow-test.cpp.o.requires

.PHONY : tests/CMakeFiles/data-flow-test.dir/requires

tests/CMakeFiles/data-flow-test.dir/clean:
	cd /home/david/tau/dg/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/data-flow-test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/data-flow-test.dir/clean

tests/CMakeFiles/data-flow-test.dir/depend:
	cd /home/david/tau/dg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/tau/dg /home/david/tau/dg/tests /home/david/tau/dg/build /home/david/tau/dg/build/tests /home/david/tau/dg/build/tests/CMakeFiles/data-flow-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/data-flow-test.dir/depend


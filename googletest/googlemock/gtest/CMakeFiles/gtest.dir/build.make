# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/s21900059/winter/FshareFuzz

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/s21900059/winter/FshareFuzz

# Include any dependencies generated for this target.
include googletest/googlemock/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include googletest/googlemock/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include googletest/googlemock/gtest/CMakeFiles/gtest.dir/flags.make

googletest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googletest/googlemock/gtest/CMakeFiles/gtest.dir/flags.make
googletest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googletest/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/s21900059/winter/FshareFuzz/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/s21900059/winter/FshareFuzz/googletest/googletest/src/gtest-all.cc

googletest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s21900059/winter/FshareFuzz/googletest/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

googletest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s21900059/winter/FshareFuzz/googletest/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

googletest/googlemock/gtest/libgtest.a: googletest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
googletest/googlemock/gtest/libgtest.a: googletest/googlemock/gtest/CMakeFiles/gtest.dir/build.make
googletest/googlemock/gtest/libgtest.a: googletest/googlemock/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/s21900059/winter/FshareFuzz/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest/googlemock/gtest/CMakeFiles/gtest.dir/build: googletest/googlemock/gtest/libgtest.a

.PHONY : googletest/googlemock/gtest/CMakeFiles/gtest.dir/build

googletest/googlemock/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : googletest/googlemock/gtest/CMakeFiles/gtest.dir/clean

googletest/googlemock/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/s21900059/winter/FshareFuzz && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/s21900059/winter/FshareFuzz /home/s21900059/winter/FshareFuzz/googletest/googletest /home/s21900059/winter/FshareFuzz /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest /home/s21900059/winter/FshareFuzz/googletest/googlemock/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googletest/googlemock/gtest/CMakeFiles/gtest.dir/depend


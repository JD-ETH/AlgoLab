# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited

# Include any dependencies generated for this target.
include CMakeFiles/protfolio-rev.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/protfolio-rev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/protfolio-rev.dir/flags.make

CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o: CMakeFiles/protfolio-rev.dir/flags.make
CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o: protfolio-rev.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o -c /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited/protfolio-rev.cpp

CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited/protfolio-rev.cpp > CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.i

CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited/protfolio-rev.cpp -o CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.s

CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.requires:
.PHONY : CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.requires

CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.provides: CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.requires
	$(MAKE) -f CMakeFiles/protfolio-rev.dir/build.make CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.provides.build
.PHONY : CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.provides

CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.provides.build: CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o

# Object files for target protfolio-rev
protfolio__rev_OBJECTS = \
"CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o"

# External object files for target protfolio-rev
protfolio__rev_EXTERNAL_OBJECTS =

protfolio-rev: CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o
protfolio-rev: CMakeFiles/protfolio-rev.dir/build.make
protfolio-rev: /usr/lib/x86_64-linux-gnu/libmpfr.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libgmp.so
protfolio-rev: /usr/local/lib/libCGAL_Core.so
protfolio-rev: /usr/local/lib/libCGAL.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libboost_thread.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libboost_system.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libpthread.so
protfolio-rev: /usr/local/lib/libCGAL_Core.so
protfolio-rev: /usr/local/lib/libCGAL.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libboost_thread.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libboost_system.so
protfolio-rev: /usr/lib/x86_64-linux-gnu/libpthread.so
protfolio-rev: CMakeFiles/protfolio-rev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable protfolio-rev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/protfolio-rev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/protfolio-rev.dir/build: protfolio-rev
.PHONY : CMakeFiles/protfolio-rev.dir/build

CMakeFiles/protfolio-rev.dir/requires: CMakeFiles/protfolio-rev.dir/protfolio-rev.cpp.o.requires
.PHONY : CMakeFiles/protfolio-rev.dir/requires

CMakeFiles/protfolio-rev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/protfolio-rev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/protfolio-rev.dir/clean

CMakeFiles/protfolio-rev.dir/depend:
	cd /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited /home/jd/eclipse_ws/AlgoLab/week13/portfolios-revisited/CMakeFiles/protfolio-rev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/protfolio-rev.dir/depend

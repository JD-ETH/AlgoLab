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
CMAKE_SOURCE_DIR = /home/jd/workspace/AlgoLab/week7/snippets

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jd/workspace/AlgoLab/week7/snippets

# Include any dependencies generated for this target.
include CMakeFiles/minimize.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/minimize.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minimize.dir/flags.make

CMakeFiles/minimize.dir/minimize.cpp.o: CMakeFiles/minimize.dir/flags.make
CMakeFiles/minimize.dir/minimize.cpp.o: minimize.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jd/workspace/AlgoLab/week7/snippets/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/minimize.dir/minimize.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/minimize.dir/minimize.cpp.o -c /home/jd/workspace/AlgoLab/week7/snippets/minimize.cpp

CMakeFiles/minimize.dir/minimize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minimize.dir/minimize.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jd/workspace/AlgoLab/week7/snippets/minimize.cpp > CMakeFiles/minimize.dir/minimize.cpp.i

CMakeFiles/minimize.dir/minimize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minimize.dir/minimize.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jd/workspace/AlgoLab/week7/snippets/minimize.cpp -o CMakeFiles/minimize.dir/minimize.cpp.s

CMakeFiles/minimize.dir/minimize.cpp.o.requires:
.PHONY : CMakeFiles/minimize.dir/minimize.cpp.o.requires

CMakeFiles/minimize.dir/minimize.cpp.o.provides: CMakeFiles/minimize.dir/minimize.cpp.o.requires
	$(MAKE) -f CMakeFiles/minimize.dir/build.make CMakeFiles/minimize.dir/minimize.cpp.o.provides.build
.PHONY : CMakeFiles/minimize.dir/minimize.cpp.o.provides

CMakeFiles/minimize.dir/minimize.cpp.o.provides.build: CMakeFiles/minimize.dir/minimize.cpp.o

# Object files for target minimize
minimize_OBJECTS = \
"CMakeFiles/minimize.dir/minimize.cpp.o"

# External object files for target minimize
minimize_EXTERNAL_OBJECTS =

minimize: CMakeFiles/minimize.dir/minimize.cpp.o
minimize: CMakeFiles/minimize.dir/build.make
minimize: /usr/lib/x86_64-linux-gnu/libmpfr.so
minimize: /usr/lib/x86_64-linux-gnu/libgmp.so
minimize: /usr/local/lib/x86_64-linux-gnu/libCGAL_Core.so.12.0.0
minimize: /usr/local/lib/x86_64-linux-gnu/libCGAL.so.12.0.0
minimize: /usr/lib/x86_64-linux-gnu/libboost_thread.so
minimize: /usr/lib/x86_64-linux-gnu/libboost_system.so
minimize: /usr/lib/x86_64-linux-gnu/libpthread.so
minimize: /usr/local/lib/x86_64-linux-gnu/libCGAL_Core.so.12.0.0
minimize: /usr/local/lib/x86_64-linux-gnu/libCGAL.so.12.0.0
minimize: /usr/lib/x86_64-linux-gnu/libboost_thread.so
minimize: /usr/lib/x86_64-linux-gnu/libboost_system.so
minimize: /usr/lib/x86_64-linux-gnu/libpthread.so
minimize: CMakeFiles/minimize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable minimize"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minimize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minimize.dir/build: minimize
.PHONY : CMakeFiles/minimize.dir/build

CMakeFiles/minimize.dir/requires: CMakeFiles/minimize.dir/minimize.cpp.o.requires
.PHONY : CMakeFiles/minimize.dir/requires

CMakeFiles/minimize.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minimize.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minimize.dir/clean

CMakeFiles/minimize.dir/depend:
	cd /home/jd/workspace/AlgoLab/week7/snippets && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jd/workspace/AlgoLab/week7/snippets /home/jd/workspace/AlgoLab/week7/snippets /home/jd/workspace/AlgoLab/week7/snippets /home/jd/workspace/AlgoLab/week7/snippets /home/jd/workspace/AlgoLab/week7/snippets/CMakeFiles/minimize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minimize.dir/depend


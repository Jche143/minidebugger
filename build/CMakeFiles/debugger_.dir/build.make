# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/jche/github/minidebugger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jche/github/minidebugger/build

# Include any dependencies generated for this target.
include CMakeFiles/debugger_.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/debugger_.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/debugger_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/debugger_.dir/flags.make

CMakeFiles/debugger_.dir/src/debugger.cpp.o: CMakeFiles/debugger_.dir/flags.make
CMakeFiles/debugger_.dir/src/debugger.cpp.o: ../src/debugger.cpp
CMakeFiles/debugger_.dir/src/debugger.cpp.o: CMakeFiles/debugger_.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jche/github/minidebugger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/debugger_.dir/src/debugger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/debugger_.dir/src/debugger.cpp.o -MF CMakeFiles/debugger_.dir/src/debugger.cpp.o.d -o CMakeFiles/debugger_.dir/src/debugger.cpp.o -c /home/jche/github/minidebugger/src/debugger.cpp

CMakeFiles/debugger_.dir/src/debugger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/debugger_.dir/src/debugger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jche/github/minidebugger/src/debugger.cpp > CMakeFiles/debugger_.dir/src/debugger.cpp.i

CMakeFiles/debugger_.dir/src/debugger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/debugger_.dir/src/debugger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jche/github/minidebugger/src/debugger.cpp -o CMakeFiles/debugger_.dir/src/debugger.cpp.s

# Object files for target debugger_
debugger__OBJECTS = \
"CMakeFiles/debugger_.dir/src/debugger.cpp.o"

# External object files for target debugger_
debugger__EXTERNAL_OBJECTS =

debugger_: CMakeFiles/debugger_.dir/src/debugger.cpp.o
debugger_: CMakeFiles/debugger_.dir/build.make
debugger_: liblinenoise.a
debugger_: CMakeFiles/debugger_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jche/github/minidebugger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable debugger_"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/debugger_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/debugger_.dir/build: debugger_
.PHONY : CMakeFiles/debugger_.dir/build

CMakeFiles/debugger_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/debugger_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/debugger_.dir/clean

CMakeFiles/debugger_.dir/depend:
	cd /home/jche/github/minidebugger/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jche/github/minidebugger /home/jche/github/minidebugger /home/jche/github/minidebugger/build /home/jche/github/minidebugger/build /home/jche/github/minidebugger/build/CMakeFiles/debugger_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/debugger_.dir/depend


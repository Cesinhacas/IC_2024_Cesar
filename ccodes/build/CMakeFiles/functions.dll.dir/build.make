# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build

# Include any dependencies generated for this target.
include CMakeFiles/functions.dll.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/functions.dll.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/functions.dll.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/functions.dll.dir/flags.make

CMakeFiles/functions.dll.dir/functions.c.o: CMakeFiles/functions.dll.dir/flags.make
CMakeFiles/functions.dll.dir/functions.c.o: functions.c
CMakeFiles/functions.dll.dir/functions.c.o: CMakeFiles/functions.dll.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/functions.dll.dir/functions.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/functions.dll.dir/functions.c.o -MF CMakeFiles/functions.dll.dir/functions.c.o.d -o CMakeFiles/functions.dll.dir/functions.c.o -c /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build/functions.c

CMakeFiles/functions.dll.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.dll.dir/functions.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build/functions.c > CMakeFiles/functions.dll.dir/functions.c.i

CMakeFiles/functions.dll.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.dll.dir/functions.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build/functions.c -o CMakeFiles/functions.dll.dir/functions.c.s

# Object files for target functions.dll
functions_dll_OBJECTS = \
"CMakeFiles/functions.dll.dir/functions.c.o"

# External object files for target functions.dll
functions_dll_EXTERNAL_OBJECTS =

functions.dll: CMakeFiles/functions.dll.dir/functions.c.o
functions.dll: CMakeFiles/functions.dll.dir/build.make
functions.dll: CMakeFiles/functions.dll.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable functions.dll"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/functions.dll.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/functions.dll.dir/build: functions.dll
.PHONY : CMakeFiles/functions.dll.dir/build

CMakeFiles/functions.dll.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/functions.dll.dir/cmake_clean.cmake
.PHONY : CMakeFiles/functions.dll.dir/clean

CMakeFiles/functions.dll.dir/depend:
	cd /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build /mnt/c/Users/LabT5/Desktop/Cesar/IC_2024_Cesar/ccodes/build/CMakeFiles/functions.dll.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/functions.dll.dir/depend


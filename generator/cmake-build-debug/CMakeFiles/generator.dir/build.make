# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /opt/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/generator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/generator.dir/flags.make

CMakeFiles/generator.dir/main.cpp.o: CMakeFiles/generator.dir/flags.make
CMakeFiles/generator.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/generator.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/generator.dir/main.cpp.o -c "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/main.cpp"

CMakeFiles/generator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/generator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/main.cpp" > CMakeFiles/generator.dir/main.cpp.i

CMakeFiles/generator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/generator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/main.cpp" -o CMakeFiles/generator.dir/main.cpp.s

CMakeFiles/generator.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/generator.dir/main.cpp.o.requires

CMakeFiles/generator.dir/main.cpp.o.provides: CMakeFiles/generator.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/generator.dir/build.make CMakeFiles/generator.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/generator.dir/main.cpp.o.provides

CMakeFiles/generator.dir/main.cpp.o.provides.build: CMakeFiles/generator.dir/main.cpp.o


# Object files for target generator
generator_OBJECTS = \
"CMakeFiles/generator.dir/main.cpp.o"

# External object files for target generator
generator_EXTERNAL_OBJECTS =

generator: CMakeFiles/generator.dir/main.cpp.o
generator: CMakeFiles/generator.dir/build.make
generator: CMakeFiles/generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/generator.dir/build: generator

.PHONY : CMakeFiles/generator.dir/build

CMakeFiles/generator.dir/requires: CMakeFiles/generator.dir/main.cpp.o.requires

.PHONY : CMakeFiles/generator.dir/requires

CMakeFiles/generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generator.dir/clean

CMakeFiles/generator.dir/depend:
	cd "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator" "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator" "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug" "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug" "/home/afonscosta/Dropbox/2º Semestre/2_CG/3_Trabalho/CG_1718/generator/cmake-build-debug/CMakeFiles/generator.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/generator.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build

# Include any dependencies generated for this target.
include CMakeFiles/program.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/program.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/program.dir/flags.make

CMakeFiles/program.dir/src/main.cpp.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/program.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/program.dir/src/main.cpp.o -c /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/src/main.cpp

CMakeFiles/program.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/program.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/src/main.cpp > CMakeFiles/program.dir/src/main.cpp.i

CMakeFiles/program.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/program.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/src/main.cpp -o CMakeFiles/program.dir/src/main.cpp.s

# Object files for target program
program_OBJECTS = \
"CMakeFiles/program.dir/src/main.cpp.o"

# External object files for target program
program_EXTERNAL_OBJECTS =

program: CMakeFiles/program.dir/src/main.cpp.o
program: CMakeFiles/program.dir/build.make
program: CMakeFiles/program.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable program"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/program.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/program.dir/build: program

.PHONY : CMakeFiles/program.dir/build

CMakeFiles/program.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/program.dir/cmake_clean.cmake
.PHONY : CMakeFiles/program.dir/clean

CMakeFiles/program.dir/depend:
	cd /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build /mnt/c/Users/alice/OneDrive/Documentos/GitHub/trabalho1-forca-Bianca-Mirtes/build/CMakeFiles/program.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/program.dir/depend


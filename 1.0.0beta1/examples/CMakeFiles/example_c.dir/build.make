# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adhawkins/libcoverart.git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adhawkins/libcoverart.git

# Include any dependencies generated for this target.
include examples/CMakeFiles/example_c.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/example_c.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/example_c.dir/flags.make

examples/CMakeFiles/example_c.dir/example_c.c.o: examples/CMakeFiles/example_c.dir/flags.make
examples/CMakeFiles/example_c.dir/example_c.c.o: examples/example_c.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/adhawkins/libcoverart.git/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/example_c.dir/example_c.c.o"
	cd /home/adhawkins/libcoverart.git/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/example_c.dir/example_c.c.o   -c /home/adhawkins/libcoverart.git/examples/example_c.c

examples/CMakeFiles/example_c.dir/example_c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/example_c.dir/example_c.c.i"
	cd /home/adhawkins/libcoverart.git/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/adhawkins/libcoverart.git/examples/example_c.c > CMakeFiles/example_c.dir/example_c.c.i

examples/CMakeFiles/example_c.dir/example_c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/example_c.dir/example_c.c.s"
	cd /home/adhawkins/libcoverart.git/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/adhawkins/libcoverart.git/examples/example_c.c -o CMakeFiles/example_c.dir/example_c.c.s

examples/CMakeFiles/example_c.dir/example_c.c.o.requires:
.PHONY : examples/CMakeFiles/example_c.dir/example_c.c.o.requires

examples/CMakeFiles/example_c.dir/example_c.c.o.provides: examples/CMakeFiles/example_c.dir/example_c.c.o.requires
	$(MAKE) -f examples/CMakeFiles/example_c.dir/build.make examples/CMakeFiles/example_c.dir/example_c.c.o.provides.build
.PHONY : examples/CMakeFiles/example_c.dir/example_c.c.o.provides

examples/CMakeFiles/example_c.dir/example_c.c.o.provides.build: examples/CMakeFiles/example_c.dir/example_c.c.o
.PHONY : examples/CMakeFiles/example_c.dir/example_c.c.o.provides.build

# Object files for target example_c
example_c_OBJECTS = \
"CMakeFiles/example_c.dir/example_c.c.o"

# External object files for target example_c
example_c_EXTERNAL_OBJECTS =

examples/example_c: examples/CMakeFiles/example_c.dir/example_c.c.o
examples/example_c: src/libcoverart.so.0.0.0
examples/example_c: /usr/lib/libneon.so
examples/example_c: /home/adhawkins/usr/lib/libjansson.so
examples/example_c: examples/CMakeFiles/example_c.dir/build.make
examples/example_c: examples/CMakeFiles/example_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable example_c"
	cd /home/adhawkins/libcoverart.git/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/example_c.dir/build: examples/example_c
.PHONY : examples/CMakeFiles/example_c.dir/build

examples/CMakeFiles/example_c.dir/requires: examples/CMakeFiles/example_c.dir/example_c.c.o.requires
.PHONY : examples/CMakeFiles/example_c.dir/requires

examples/CMakeFiles/example_c.dir/clean:
	cd /home/adhawkins/libcoverart.git/examples && $(CMAKE_COMMAND) -P CMakeFiles/example_c.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/example_c.dir/clean

examples/CMakeFiles/example_c.dir/depend:
	cd /home/adhawkins/libcoverart.git && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adhawkins/libcoverart.git /home/adhawkins/libcoverart.git/examples /home/adhawkins/libcoverart.git /home/adhawkins/libcoverart.git/examples /home/adhawkins/libcoverart.git/examples/CMakeFiles/example_c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/example_c.dir/depend


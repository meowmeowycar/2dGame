# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.3.5\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.3.5\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\agnie\Documents\GitHub\2dGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug

# Include any dependencies generated for this target.
include _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/flags.make

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/flags.make
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/includes_C.rsp
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj: _deps/flac-src/microbench/benchmark_residual.c
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && C:\PROGRA~1\JETBRA~1\CLION2~1.5\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj -MF CMakeFiles\benchmark_residual.dir\benchmark_residual.c.obj.d -o CMakeFiles\benchmark_residual.dir\benchmark_residual.c.obj -c C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench\benchmark_residual.c

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/benchmark_residual.dir/benchmark_residual.c.i"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && C:\PROGRA~1\JETBRA~1\CLION2~1.5\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench\benchmark_residual.c > CMakeFiles\benchmark_residual.dir\benchmark_residual.c.i

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/benchmark_residual.dir/benchmark_residual.c.s"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && C:\PROGRA~1\JETBRA~1\CLION2~1.5\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench\benchmark_residual.c -o CMakeFiles\benchmark_residual.dir\benchmark_residual.c.s

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/flags.make
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/includes_C.rsp
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj: _deps/flac-src/microbench/util.c
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && C:\PROGRA~1\JETBRA~1\CLION2~1.5\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj -MF CMakeFiles\benchmark_residual.dir\util.c.obj.d -o CMakeFiles\benchmark_residual.dir\util.c.obj -c C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench\util.c

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/benchmark_residual.dir/util.c.i"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && C:\PROGRA~1\JETBRA~1\CLION2~1.5\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench\util.c > CMakeFiles\benchmark_residual.dir\util.c.i

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/benchmark_residual.dir/util.c.s"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && C:\PROGRA~1\JETBRA~1\CLION2~1.5\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench\util.c -o CMakeFiles\benchmark_residual.dir\util.c.s

# Object files for target benchmark_residual
benchmark_residual_OBJECTS = \
"CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj" \
"CMakeFiles/benchmark_residual.dir/util.c.obj"

# External object files for target benchmark_residual
benchmark_residual_EXTERNAL_OBJECTS =

objs/benchmark_residual.exe: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/benchmark_residual.c.obj
objs/benchmark_residual.exe: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/util.c.obj
objs/benchmark_residual.exe: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/build.make
objs/benchmark_residual.exe: _deps/sfml-build/lib/libFLACd.a
objs/benchmark_residual.exe: _deps/sfml-build/lib/liboggd.a
objs/benchmark_residual.exe: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/linkLibs.rsp
objs/benchmark_residual.exe: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/objects1.rsp
objs/benchmark_residual.exe: _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ..\..\..\objs\benchmark_residual.exe"
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\benchmark_residual.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/build: objs/benchmark_residual.exe
.PHONY : _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/build

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/clean:
	cd /d C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench && $(CMAKE_COMMAND) -P CMakeFiles\benchmark_residual.dir\cmake_clean.cmake
.PHONY : _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/clean

_deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\agnie\Documents\GitHub\2dGame C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-src\microbench C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench C:\Users\agnie\Documents\GitHub\2dGame\cmake-build-debug\_deps\flac-build\microbench\CMakeFiles\benchmark_residual.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/flac-build/microbench/CMakeFiles/benchmark_residual.dir/depend


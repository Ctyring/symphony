# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /root/cty/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/cty/sylar

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /root/cty/sylar/CMakeFiles /root/cty/sylar//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /root/cty/sylar/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named sylar

# Build rule for target.
sylar: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 sylar
.PHONY : sylar

# fast build rule for target.
sylar/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/build
.PHONY : sylar/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named test_config

# Build rule for target.
test_config: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_config
.PHONY : test_config

# fast build rule for target.
test_config/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/build
.PHONY : test_config/fast

sylar/config.o: sylar/config.cc.o
.PHONY : sylar/config.o

# target to build an object file
sylar/config.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/config.cc.o
.PHONY : sylar/config.cc.o

sylar/config.i: sylar/config.cc.i
.PHONY : sylar/config.i

# target to preprocess a source file
sylar/config.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/config.cc.i
.PHONY : sylar/config.cc.i

sylar/config.s: sylar/config.cc.s
.PHONY : sylar/config.s

# target to generate assembly for a file
sylar/config.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/config.cc.s
.PHONY : sylar/config.cc.s

sylar/log.o: sylar/log.cc.o
.PHONY : sylar/log.o

# target to build an object file
sylar/log.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/log.cc.o
.PHONY : sylar/log.cc.o

sylar/log.i: sylar/log.cc.i
.PHONY : sylar/log.i

# target to preprocess a source file
sylar/log.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/log.cc.i
.PHONY : sylar/log.cc.i

sylar/log.s: sylar/log.cc.s
.PHONY : sylar/log.s

# target to generate assembly for a file
sylar/log.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/log.cc.s
.PHONY : sylar/log.cc.s

sylar/util.o: sylar/util.cc.o
.PHONY : sylar/util.o

# target to build an object file
sylar/util.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/util.cc.o
.PHONY : sylar/util.cc.o

sylar/util.i: sylar/util.cc.i
.PHONY : sylar/util.i

# target to preprocess a source file
sylar/util.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/util.cc.i
.PHONY : sylar/util.cc.i

sylar/util.s: sylar/util.cc.s
.PHONY : sylar/util.s

# target to generate assembly for a file
sylar/util.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/util.cc.s
.PHONY : sylar/util.cc.s

tests/test.o: tests/test.cc.o
.PHONY : tests/test.o

# target to build an object file
tests/test.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cc.o
.PHONY : tests/test.cc.o

tests/test.i: tests/test.cc.i
.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cc.i
.PHONY : tests/test.cc.i

tests/test.s: tests/test.cc.s
.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cc.s
.PHONY : tests/test.cc.s

tests/test_config.o: tests/test_config.cc.o
.PHONY : tests/test_config.o

# target to build an object file
tests/test_config.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.o
.PHONY : tests/test_config.cc.o

tests/test_config.i: tests/test_config.cc.i
.PHONY : tests/test_config.i

# target to preprocess a source file
tests/test_config.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.i
.PHONY : tests/test_config.cc.i

tests/test_config.s: tests/test_config.cc.s
.PHONY : tests/test_config.s

# target to generate assembly for a file
tests/test_config.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.s
.PHONY : tests/test_config.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... sylar"
	@echo "... test"
	@echo "... test_config"
	@echo "... sylar/config.o"
	@echo "... sylar/config.i"
	@echo "... sylar/config.s"
	@echo "... sylar/log.o"
	@echo "... sylar/log.i"
	@echo "... sylar/log.s"
	@echo "... sylar/util.o"
	@echo "... sylar/util.i"
	@echo "... sylar/util.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


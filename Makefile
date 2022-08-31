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

#=============================================================================
# Target rules for targets named test_thread

# Build rule for target.
test_thread: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_thread
.PHONY : test_thread

# fast build rule for target.
test_thread/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/build
.PHONY : test_thread/fast

#=============================================================================
# Target rules for targets named test_util

# Build rule for target.
test_util: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_util
.PHONY : test_util

# fast build rule for target.
test_util/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/build
.PHONY : test_util/fast

#=============================================================================
# Target rules for targets named test_fiber

# Build rule for target.
test_fiber: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_fiber
.PHONY : test_fiber

# fast build rule for target.
test_fiber/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/build
.PHONY : test_fiber/fast

#=============================================================================
# Target rules for targets named test_scheduler

# Build rule for target.
test_scheduler: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_scheduler
.PHONY : test_scheduler

# fast build rule for target.
test_scheduler/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/build
.PHONY : test_scheduler/fast

#=============================================================================
# Target rules for targets named test_iomanager

# Build rule for target.
test_iomanager: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_iomanager
.PHONY : test_iomanager

# fast build rule for target.
test_iomanager/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/build
.PHONY : test_iomanager/fast

#=============================================================================
# Target rules for targets named test_hook

# Build rule for target.
test_hook: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_hook
.PHONY : test_hook

# fast build rule for target.
test_hook/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/build
.PHONY : test_hook/fast

#=============================================================================
# Target rules for targets named test_address

# Build rule for target.
test_address: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_address
.PHONY : test_address

# fast build rule for target.
test_address/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/build
.PHONY : test_address/fast

#=============================================================================
# Target rules for targets named test_socket

# Build rule for target.
test_socket: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_socket
.PHONY : test_socket

# fast build rule for target.
test_socket/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/build
.PHONY : test_socket/fast

#=============================================================================
# Target rules for targets named test_bytearray

# Build rule for target.
test_bytearray: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_bytearray
.PHONY : test_bytearray

# fast build rule for target.
test_bytearray/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_bytearray.dir/build.make CMakeFiles/test_bytearray.dir/build
.PHONY : test_bytearray/fast

#=============================================================================
# Target rules for targets named test_http

# Build rule for target.
test_http: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_http
.PHONY : test_http

# fast build rule for target.
test_http/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_http.dir/build.make CMakeFiles/test_http.dir/build
.PHONY : test_http/fast

sylar/address.o: sylar/address.cc.o
.PHONY : sylar/address.o

# target to build an object file
sylar/address.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/address.cc.o
.PHONY : sylar/address.cc.o

sylar/address.i: sylar/address.cc.i
.PHONY : sylar/address.i

# target to preprocess a source file
sylar/address.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/address.cc.i
.PHONY : sylar/address.cc.i

sylar/address.s: sylar/address.cc.s
.PHONY : sylar/address.s

# target to generate assembly for a file
sylar/address.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/address.cc.s
.PHONY : sylar/address.cc.s

sylar/bytearray.o: sylar/bytearray.cc.o
.PHONY : sylar/bytearray.o

# target to build an object file
sylar/bytearray.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/bytearray.cc.o
.PHONY : sylar/bytearray.cc.o

sylar/bytearray.i: sylar/bytearray.cc.i
.PHONY : sylar/bytearray.i

# target to preprocess a source file
sylar/bytearray.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/bytearray.cc.i
.PHONY : sylar/bytearray.cc.i

sylar/bytearray.s: sylar/bytearray.cc.s
.PHONY : sylar/bytearray.s

# target to generate assembly for a file
sylar/bytearray.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/bytearray.cc.s
.PHONY : sylar/bytearray.cc.s

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

sylar/fd_manager.o: sylar/fd_manager.cc.o
.PHONY : sylar/fd_manager.o

# target to build an object file
sylar/fd_manager.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/fd_manager.cc.o
.PHONY : sylar/fd_manager.cc.o

sylar/fd_manager.i: sylar/fd_manager.cc.i
.PHONY : sylar/fd_manager.i

# target to preprocess a source file
sylar/fd_manager.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/fd_manager.cc.i
.PHONY : sylar/fd_manager.cc.i

sylar/fd_manager.s: sylar/fd_manager.cc.s
.PHONY : sylar/fd_manager.s

# target to generate assembly for a file
sylar/fd_manager.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/fd_manager.cc.s
.PHONY : sylar/fd_manager.cc.s

sylar/fiber.o: sylar/fiber.cc.o
.PHONY : sylar/fiber.o

# target to build an object file
sylar/fiber.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/fiber.cc.o
.PHONY : sylar/fiber.cc.o

sylar/fiber.i: sylar/fiber.cc.i
.PHONY : sylar/fiber.i

# target to preprocess a source file
sylar/fiber.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/fiber.cc.i
.PHONY : sylar/fiber.cc.i

sylar/fiber.s: sylar/fiber.cc.s
.PHONY : sylar/fiber.s

# target to generate assembly for a file
sylar/fiber.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/fiber.cc.s
.PHONY : sylar/fiber.cc.s

sylar/hook.o: sylar/hook.cc.o
.PHONY : sylar/hook.o

# target to build an object file
sylar/hook.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/hook.cc.o
.PHONY : sylar/hook.cc.o

sylar/hook.i: sylar/hook.cc.i
.PHONY : sylar/hook.i

# target to preprocess a source file
sylar/hook.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/hook.cc.i
.PHONY : sylar/hook.cc.i

sylar/hook.s: sylar/hook.cc.s
.PHONY : sylar/hook.s

# target to generate assembly for a file
sylar/hook.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/hook.cc.s
.PHONY : sylar/hook.cc.s

sylar/http/http.o: sylar/http/http.cc.o
.PHONY : sylar/http/http.o

# target to build an object file
sylar/http/http.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/http/http.cc.o
.PHONY : sylar/http/http.cc.o

sylar/http/http.i: sylar/http/http.cc.i
.PHONY : sylar/http/http.i

# target to preprocess a source file
sylar/http/http.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/http/http.cc.i
.PHONY : sylar/http/http.cc.i

sylar/http/http.s: sylar/http/http.cc.s
.PHONY : sylar/http/http.s

# target to generate assembly for a file
sylar/http/http.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/http/http.cc.s
.PHONY : sylar/http/http.cc.s

sylar/iomanager.o: sylar/iomanager.cc.o
.PHONY : sylar/iomanager.o

# target to build an object file
sylar/iomanager.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/iomanager.cc.o
.PHONY : sylar/iomanager.cc.o

sylar/iomanager.i: sylar/iomanager.cc.i
.PHONY : sylar/iomanager.i

# target to preprocess a source file
sylar/iomanager.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/iomanager.cc.i
.PHONY : sylar/iomanager.cc.i

sylar/iomanager.s: sylar/iomanager.cc.s
.PHONY : sylar/iomanager.s

# target to generate assembly for a file
sylar/iomanager.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/iomanager.cc.s
.PHONY : sylar/iomanager.cc.s

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

sylar/scheduler.o: sylar/scheduler.cc.o
.PHONY : sylar/scheduler.o

# target to build an object file
sylar/scheduler.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/scheduler.cc.o
.PHONY : sylar/scheduler.cc.o

sylar/scheduler.i: sylar/scheduler.cc.i
.PHONY : sylar/scheduler.i

# target to preprocess a source file
sylar/scheduler.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/scheduler.cc.i
.PHONY : sylar/scheduler.cc.i

sylar/scheduler.s: sylar/scheduler.cc.s
.PHONY : sylar/scheduler.s

# target to generate assembly for a file
sylar/scheduler.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/scheduler.cc.s
.PHONY : sylar/scheduler.cc.s

sylar/socket.o: sylar/socket.cc.o
.PHONY : sylar/socket.o

# target to build an object file
sylar/socket.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/socket.cc.o
.PHONY : sylar/socket.cc.o

sylar/socket.i: sylar/socket.cc.i
.PHONY : sylar/socket.i

# target to preprocess a source file
sylar/socket.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/socket.cc.i
.PHONY : sylar/socket.cc.i

sylar/socket.s: sylar/socket.cc.s
.PHONY : sylar/socket.s

# target to generate assembly for a file
sylar/socket.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/socket.cc.s
.PHONY : sylar/socket.cc.s

sylar/thread.o: sylar/thread.cc.o
.PHONY : sylar/thread.o

# target to build an object file
sylar/thread.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/thread.cc.o
.PHONY : sylar/thread.cc.o

sylar/thread.i: sylar/thread.cc.i
.PHONY : sylar/thread.i

# target to preprocess a source file
sylar/thread.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/thread.cc.i
.PHONY : sylar/thread.cc.i

sylar/thread.s: sylar/thread.cc.s
.PHONY : sylar/thread.s

# target to generate assembly for a file
sylar/thread.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/thread.cc.s
.PHONY : sylar/thread.cc.s

sylar/timer.o: sylar/timer.cc.o
.PHONY : sylar/timer.o

# target to build an object file
sylar/timer.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/timer.cc.o
.PHONY : sylar/timer.cc.o

sylar/timer.i: sylar/timer.cc.i
.PHONY : sylar/timer.i

# target to preprocess a source file
sylar/timer.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/timer.cc.i
.PHONY : sylar/timer.cc.i

sylar/timer.s: sylar/timer.cc.s
.PHONY : sylar/timer.s

# target to generate assembly for a file
sylar/timer.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/timer.cc.s
.PHONY : sylar/timer.cc.s

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

tests/test_address.o: tests/test_address.cc.o
.PHONY : tests/test_address.o

# target to build an object file
tests/test_address.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cc.o
.PHONY : tests/test_address.cc.o

tests/test_address.i: tests/test_address.cc.i
.PHONY : tests/test_address.i

# target to preprocess a source file
tests/test_address.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cc.i
.PHONY : tests/test_address.cc.i

tests/test_address.s: tests/test_address.cc.s
.PHONY : tests/test_address.s

# target to generate assembly for a file
tests/test_address.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cc.s
.PHONY : tests/test_address.cc.s

tests/test_bytearray.o: tests/test_bytearray.cc.o
.PHONY : tests/test_bytearray.o

# target to build an object file
tests/test_bytearray.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_bytearray.dir/build.make CMakeFiles/test_bytearray.dir/tests/test_bytearray.cc.o
.PHONY : tests/test_bytearray.cc.o

tests/test_bytearray.i: tests/test_bytearray.cc.i
.PHONY : tests/test_bytearray.i

# target to preprocess a source file
tests/test_bytearray.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_bytearray.dir/build.make CMakeFiles/test_bytearray.dir/tests/test_bytearray.cc.i
.PHONY : tests/test_bytearray.cc.i

tests/test_bytearray.s: tests/test_bytearray.cc.s
.PHONY : tests/test_bytearray.s

# target to generate assembly for a file
tests/test_bytearray.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_bytearray.dir/build.make CMakeFiles/test_bytearray.dir/tests/test_bytearray.cc.s
.PHONY : tests/test_bytearray.cc.s

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

tests/test_fiber.o: tests/test_fiber.cc.o
.PHONY : tests/test_fiber.o

# target to build an object file
tests/test_fiber.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.o
.PHONY : tests/test_fiber.cc.o

tests/test_fiber.i: tests/test_fiber.cc.i
.PHONY : tests/test_fiber.i

# target to preprocess a source file
tests/test_fiber.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.i
.PHONY : tests/test_fiber.cc.i

tests/test_fiber.s: tests/test_fiber.cc.s
.PHONY : tests/test_fiber.s

# target to generate assembly for a file
tests/test_fiber.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.s
.PHONY : tests/test_fiber.cc.s

tests/test_hook.o: tests/test_hook.cc.o
.PHONY : tests/test_hook.o

# target to build an object file
tests/test_hook.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.o
.PHONY : tests/test_hook.cc.o

tests/test_hook.i: tests/test_hook.cc.i
.PHONY : tests/test_hook.i

# target to preprocess a source file
tests/test_hook.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.i
.PHONY : tests/test_hook.cc.i

tests/test_hook.s: tests/test_hook.cc.s
.PHONY : tests/test_hook.s

# target to generate assembly for a file
tests/test_hook.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.s
.PHONY : tests/test_hook.cc.s

tests/test_http.o: tests/test_http.cc.o
.PHONY : tests/test_http.o

# target to build an object file
tests/test_http.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_http.dir/build.make CMakeFiles/test_http.dir/tests/test_http.cc.o
.PHONY : tests/test_http.cc.o

tests/test_http.i: tests/test_http.cc.i
.PHONY : tests/test_http.i

# target to preprocess a source file
tests/test_http.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_http.dir/build.make CMakeFiles/test_http.dir/tests/test_http.cc.i
.PHONY : tests/test_http.cc.i

tests/test_http.s: tests/test_http.cc.s
.PHONY : tests/test_http.s

# target to generate assembly for a file
tests/test_http.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_http.dir/build.make CMakeFiles/test_http.dir/tests/test_http.cc.s
.PHONY : tests/test_http.cc.s

tests/test_iomanager.o: tests/test_iomanager.cc.o
.PHONY : tests/test_iomanager.o

# target to build an object file
tests/test_iomanager.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.o
.PHONY : tests/test_iomanager.cc.o

tests/test_iomanager.i: tests/test_iomanager.cc.i
.PHONY : tests/test_iomanager.i

# target to preprocess a source file
tests/test_iomanager.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.i
.PHONY : tests/test_iomanager.cc.i

tests/test_iomanager.s: tests/test_iomanager.cc.s
.PHONY : tests/test_iomanager.s

# target to generate assembly for a file
tests/test_iomanager.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.s
.PHONY : tests/test_iomanager.cc.s

tests/test_scheduler.o: tests/test_scheduler.cc.o
.PHONY : tests/test_scheduler.o

# target to build an object file
tests/test_scheduler.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.o
.PHONY : tests/test_scheduler.cc.o

tests/test_scheduler.i: tests/test_scheduler.cc.i
.PHONY : tests/test_scheduler.i

# target to preprocess a source file
tests/test_scheduler.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.i
.PHONY : tests/test_scheduler.cc.i

tests/test_scheduler.s: tests/test_scheduler.cc.s
.PHONY : tests/test_scheduler.s

# target to generate assembly for a file
tests/test_scheduler.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.s
.PHONY : tests/test_scheduler.cc.s

tests/test_socket.o: tests/test_socket.cc.o
.PHONY : tests/test_socket.o

# target to build an object file
tests/test_socket.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/tests/test_socket.cc.o
.PHONY : tests/test_socket.cc.o

tests/test_socket.i: tests/test_socket.cc.i
.PHONY : tests/test_socket.i

# target to preprocess a source file
tests/test_socket.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/tests/test_socket.cc.i
.PHONY : tests/test_socket.cc.i

tests/test_socket.s: tests/test_socket.cc.s
.PHONY : tests/test_socket.s

# target to generate assembly for a file
tests/test_socket.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/tests/test_socket.cc.s
.PHONY : tests/test_socket.cc.s

tests/test_thread.o: tests/test_thread.cc.o
.PHONY : tests/test_thread.o

# target to build an object file
tests/test_thread.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.o
.PHONY : tests/test_thread.cc.o

tests/test_thread.i: tests/test_thread.cc.i
.PHONY : tests/test_thread.i

# target to preprocess a source file
tests/test_thread.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.i
.PHONY : tests/test_thread.cc.i

tests/test_thread.s: tests/test_thread.cc.s
.PHONY : tests/test_thread.s

# target to generate assembly for a file
tests/test_thread.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.s
.PHONY : tests/test_thread.cc.s

tests/test_util.o: tests/test_util.cc.o
.PHONY : tests/test_util.o

# target to build an object file
tests/test_util.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.o
.PHONY : tests/test_util.cc.o

tests/test_util.i: tests/test_util.cc.i
.PHONY : tests/test_util.i

# target to preprocess a source file
tests/test_util.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.i
.PHONY : tests/test_util.cc.i

tests/test_util.s: tests/test_util.cc.s
.PHONY : tests/test_util.s

# target to generate assembly for a file
tests/test_util.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.s
.PHONY : tests/test_util.cc.s

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
	@echo "... test_address"
	@echo "... test_bytearray"
	@echo "... test_config"
	@echo "... test_fiber"
	@echo "... test_hook"
	@echo "... test_http"
	@echo "... test_iomanager"
	@echo "... test_scheduler"
	@echo "... test_socket"
	@echo "... test_thread"
	@echo "... test_util"
	@echo "... sylar/address.o"
	@echo "... sylar/address.i"
	@echo "... sylar/address.s"
	@echo "... sylar/bytearray.o"
	@echo "... sylar/bytearray.i"
	@echo "... sylar/bytearray.s"
	@echo "... sylar/config.o"
	@echo "... sylar/config.i"
	@echo "... sylar/config.s"
	@echo "... sylar/fd_manager.o"
	@echo "... sylar/fd_manager.i"
	@echo "... sylar/fd_manager.s"
	@echo "... sylar/fiber.o"
	@echo "... sylar/fiber.i"
	@echo "... sylar/fiber.s"
	@echo "... sylar/hook.o"
	@echo "... sylar/hook.i"
	@echo "... sylar/hook.s"
	@echo "... sylar/http/http.o"
	@echo "... sylar/http/http.i"
	@echo "... sylar/http/http.s"
	@echo "... sylar/iomanager.o"
	@echo "... sylar/iomanager.i"
	@echo "... sylar/iomanager.s"
	@echo "... sylar/log.o"
	@echo "... sylar/log.i"
	@echo "... sylar/log.s"
	@echo "... sylar/scheduler.o"
	@echo "... sylar/scheduler.i"
	@echo "... sylar/scheduler.s"
	@echo "... sylar/socket.o"
	@echo "... sylar/socket.i"
	@echo "... sylar/socket.s"
	@echo "... sylar/thread.o"
	@echo "... sylar/thread.i"
	@echo "... sylar/thread.s"
	@echo "... sylar/timer.o"
	@echo "... sylar/timer.i"
	@echo "... sylar/timer.s"
	@echo "... sylar/util.o"
	@echo "... sylar/util.i"
	@echo "... sylar/util.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
	@echo "... tests/test_address.o"
	@echo "... tests/test_address.i"
	@echo "... tests/test_address.s"
	@echo "... tests/test_bytearray.o"
	@echo "... tests/test_bytearray.i"
	@echo "... tests/test_bytearray.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
	@echo "... tests/test_fiber.o"
	@echo "... tests/test_fiber.i"
	@echo "... tests/test_fiber.s"
	@echo "... tests/test_hook.o"
	@echo "... tests/test_hook.i"
	@echo "... tests/test_hook.s"
	@echo "... tests/test_http.o"
	@echo "... tests/test_http.i"
	@echo "... tests/test_http.s"
	@echo "... tests/test_iomanager.o"
	@echo "... tests/test_iomanager.i"
	@echo "... tests/test_iomanager.s"
	@echo "... tests/test_scheduler.o"
	@echo "... tests/test_scheduler.i"
	@echo "... tests/test_scheduler.s"
	@echo "... tests/test_socket.o"
	@echo "... tests/test_socket.i"
	@echo "... tests/test_socket.s"
	@echo "... tests/test_thread.o"
	@echo "... tests/test_thread.i"
	@echo "... tests/test_thread.s"
	@echo "... tests/test_util.o"
	@echo "... tests/test_util.i"
	@echo "... tests/test_util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


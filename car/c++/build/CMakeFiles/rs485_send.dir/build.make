# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /root/workspace/car/c++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/car/c++/build

# Include any dependencies generated for this target.
include CMakeFiles/rs485_send.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rs485_send.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rs485_send.dir/flags.make

CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o: CMakeFiles/rs485_send.dir/flags.make
CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o: ../demo/rs485_send.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/car/c++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o -c /root/workspace/car/c++/demo/rs485_send.cpp

CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/car/c++/demo/rs485_send.cpp > CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.i

CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/car/c++/demo/rs485_send.cpp -o CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.s

CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.requires:

.PHONY : CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.requires

CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.provides: CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.requires
	$(MAKE) -f CMakeFiles/rs485_send.dir/build.make CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.provides.build
.PHONY : CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.provides

CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.provides.build: CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o


# Object files for target rs485_send
rs485_send_OBJECTS = \
"CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o"

# External object files for target rs485_send
rs485_send_EXTERNAL_OBJECTS =

rs485_send: CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o
rs485_send: CMakeFiles/rs485_send.dir/build.make
rs485_send: /usr/local/lib/libopencv_dnn.so.3.4.3
rs485_send: /usr/local/lib/libopencv_ml.so.3.4.3
rs485_send: /usr/local/lib/libopencv_objdetect.so.3.4.3
rs485_send: /usr/local/lib/libopencv_shape.so.3.4.3
rs485_send: /usr/local/lib/libopencv_stitching.so.3.4.3
rs485_send: /usr/local/lib/libopencv_superres.so.3.4.3
rs485_send: /usr/local/lib/libopencv_videostab.so.3.4.3
rs485_send: /usr/local/lib/libopencv_calib3d.so.3.4.3
rs485_send: /usr/local/lib/libopencv_features2d.so.3.4.3
rs485_send: /usr/local/lib/libopencv_flann.so.3.4.3
rs485_send: /usr/local/lib/libopencv_highgui.so.3.4.3
rs485_send: /usr/local/lib/libopencv_photo.so.3.4.3
rs485_send: /usr/local/lib/libopencv_video.so.3.4.3
rs485_send: /usr/local/lib/libopencv_videoio.so.3.4.3
rs485_send: /usr/local/lib/libopencv_imgcodecs.so.3.4.3
rs485_send: /usr/local/lib/libopencv_imgproc.so.3.4.3
rs485_send: /usr/local/lib/libopencv_core.so.3.4.3
rs485_send: CMakeFiles/rs485_send.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/car/c++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rs485_send"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rs485_send.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rs485_send.dir/build: rs485_send

.PHONY : CMakeFiles/rs485_send.dir/build

CMakeFiles/rs485_send.dir/requires: CMakeFiles/rs485_send.dir/demo/rs485_send.cpp.o.requires

.PHONY : CMakeFiles/rs485_send.dir/requires

CMakeFiles/rs485_send.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rs485_send.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rs485_send.dir/clean

CMakeFiles/rs485_send.dir/depend:
	cd /root/workspace/car/c++/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/car/c++ /root/workspace/car/c++ /root/workspace/car/c++/build /root/workspace/car/c++/build /root/workspace/car/c++/build/CMakeFiles/rs485_send.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rs485_send.dir/depend


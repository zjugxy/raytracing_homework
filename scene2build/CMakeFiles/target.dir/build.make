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
CMAKE_SOURCE_DIR = /home/gxy/homework/raytracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gxy/homework/raytracing/scene2build

# Include any dependencies generated for this target.
include CMakeFiles/target.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/target.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/target.dir/flags.make

CMakeFiles/target.dir/src/AABB.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/AABB.cpp.o: ../src/AABB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/target.dir/src/AABB.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/AABB.cpp.o -c /home/gxy/homework/raytracing/src/AABB.cpp

CMakeFiles/target.dir/src/AABB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/AABB.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/AABB.cpp > CMakeFiles/target.dir/src/AABB.cpp.i

CMakeFiles/target.dir/src/AABB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/AABB.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/AABB.cpp -o CMakeFiles/target.dir/src/AABB.cpp.s

CMakeFiles/target.dir/src/BVHNode.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/BVHNode.cpp.o: ../src/BVHNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/target.dir/src/BVHNode.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/BVHNode.cpp.o -c /home/gxy/homework/raytracing/src/BVHNode.cpp

CMakeFiles/target.dir/src/BVHNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/BVHNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/BVHNode.cpp > CMakeFiles/target.dir/src/BVHNode.cpp.i

CMakeFiles/target.dir/src/BVHNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/BVHNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/BVHNode.cpp -o CMakeFiles/target.dir/src/BVHNode.cpp.s

CMakeFiles/target.dir/src/Texture.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/Texture.cpp.o: ../src/Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/target.dir/src/Texture.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/Texture.cpp.o -c /home/gxy/homework/raytracing/src/Texture.cpp

CMakeFiles/target.dir/src/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/Texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/Texture.cpp > CMakeFiles/target.dir/src/Texture.cpp.i

CMakeFiles/target.dir/src/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/Texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/Texture.cpp -o CMakeFiles/target.dir/src/Texture.cpp.s

CMakeFiles/target.dir/src/Triangle.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/Triangle.cpp.o: ../src/Triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/target.dir/src/Triangle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/Triangle.cpp.o -c /home/gxy/homework/raytracing/src/Triangle.cpp

CMakeFiles/target.dir/src/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/Triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/Triangle.cpp > CMakeFiles/target.dir/src/Triangle.cpp.i

CMakeFiles/target.dir/src/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/Triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/Triangle.cpp -o CMakeFiles/target.dir/src/Triangle.cpp.s

CMakeFiles/target.dir/src/camera.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/target.dir/src/camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/camera.cpp.o -c /home/gxy/homework/raytracing/src/camera.cpp

CMakeFiles/target.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/camera.cpp > CMakeFiles/target.dir/src/camera.cpp.i

CMakeFiles/target.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/camera.cpp -o CMakeFiles/target.dir/src/camera.cpp.s

CMakeFiles/target.dir/src/main.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/target.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/main.cpp.o -c /home/gxy/homework/raytracing/src/main.cpp

CMakeFiles/target.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/main.cpp > CMakeFiles/target.dir/src/main.cpp.i

CMakeFiles/target.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/main.cpp -o CMakeFiles/target.dir/src/main.cpp.s

CMakeFiles/target.dir/src/mymath.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/mymath.cpp.o: ../src/mymath.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/target.dir/src/mymath.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/mymath.cpp.o -c /home/gxy/homework/raytracing/src/mymath.cpp

CMakeFiles/target.dir/src/mymath.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/mymath.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/mymath.cpp > CMakeFiles/target.dir/src/mymath.cpp.i

CMakeFiles/target.dir/src/mymath.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/mymath.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/mymath.cpp -o CMakeFiles/target.dir/src/mymath.cpp.s

CMakeFiles/target.dir/src/scene.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/scene.cpp.o: ../src/scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/target.dir/src/scene.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/scene.cpp.o -c /home/gxy/homework/raytracing/src/scene.cpp

CMakeFiles/target.dir/src/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/scene.cpp > CMakeFiles/target.dir/src/scene.cpp.i

CMakeFiles/target.dir/src/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/scene.cpp -o CMakeFiles/target.dir/src/scene.cpp.s

CMakeFiles/target.dir/src/tinyxml2.cpp.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/src/tinyxml2.cpp.o: ../src/tinyxml2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/target.dir/src/tinyxml2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/target.dir/src/tinyxml2.cpp.o -c /home/gxy/homework/raytracing/src/tinyxml2.cpp

CMakeFiles/target.dir/src/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/target.dir/src/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxy/homework/raytracing/src/tinyxml2.cpp > CMakeFiles/target.dir/src/tinyxml2.cpp.i

CMakeFiles/target.dir/src/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/target.dir/src/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxy/homework/raytracing/src/tinyxml2.cpp -o CMakeFiles/target.dir/src/tinyxml2.cpp.s

# Object files for target target
target_OBJECTS = \
"CMakeFiles/target.dir/src/AABB.cpp.o" \
"CMakeFiles/target.dir/src/BVHNode.cpp.o" \
"CMakeFiles/target.dir/src/Texture.cpp.o" \
"CMakeFiles/target.dir/src/Triangle.cpp.o" \
"CMakeFiles/target.dir/src/camera.cpp.o" \
"CMakeFiles/target.dir/src/main.cpp.o" \
"CMakeFiles/target.dir/src/mymath.cpp.o" \
"CMakeFiles/target.dir/src/scene.cpp.o" \
"CMakeFiles/target.dir/src/tinyxml2.cpp.o"

# External object files for target target
target_EXTERNAL_OBJECTS =

target: CMakeFiles/target.dir/src/AABB.cpp.o
target: CMakeFiles/target.dir/src/BVHNode.cpp.o
target: CMakeFiles/target.dir/src/Texture.cpp.o
target: CMakeFiles/target.dir/src/Triangle.cpp.o
target: CMakeFiles/target.dir/src/camera.cpp.o
target: CMakeFiles/target.dir/src/main.cpp.o
target: CMakeFiles/target.dir/src/mymath.cpp.o
target: CMakeFiles/target.dir/src/scene.cpp.o
target: CMakeFiles/target.dir/src/tinyxml2.cpp.o
target: CMakeFiles/target.dir/build.make
target: /usr/local/lib/libtinyobjloader.a
target: CMakeFiles/target.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gxy/homework/raytracing/scene2build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable target"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/target.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/target.dir/build: target

.PHONY : CMakeFiles/target.dir/build

CMakeFiles/target.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/target.dir/cmake_clean.cmake
.PHONY : CMakeFiles/target.dir/clean

CMakeFiles/target.dir/depend:
	cd /home/gxy/homework/raytracing/scene2build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gxy/homework/raytracing /home/gxy/homework/raytracing /home/gxy/homework/raytracing/scene2build /home/gxy/homework/raytracing/scene2build /home/gxy/homework/raytracing/scene2build/CMakeFiles/target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/target.dir/depend


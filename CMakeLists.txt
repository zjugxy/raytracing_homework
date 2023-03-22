cmake_minimum_required(VERSION 3.13)

project(raytrace)

file(GLOB src_list "src/*.cpp")
find_library(TINYOBJ_LIB tinyobjloader PATHS /usr/local/lib/)
include_directories(3rd)
include_directories(inc)
add_executable(target ${src_list})
target_link_libraries(target ${TINYOBJ_LIB})
cmake_minimum_required(VERSION 3.13)

project(raytrace)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")





file(GLOB src_list "src/*.cpp")
find_library(TINYOBJ_LIB tinyobjloader PATHS /usr/local/lib/)
include_directories(3rd)
include_directories(inc)
add_executable(target ${src_list})
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(target PUBLIC OpenMP::OpenMP_CXX ${TINYOBJ_LIB})
endif()
# target_link_libraries(target ${TINYOBJ_LIB})

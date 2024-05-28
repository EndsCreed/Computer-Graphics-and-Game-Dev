cmake_minimum_required(VERSION 3.28)
project(OpenGL_CLion)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(source_dir "${PROJECT_SOURCE_DIR}/src")
set(dep_dir "${PROJECT_SOURCE_DIR}/Dependencies")

file(GLOB source_files "${source_dir}/*.cpp")

include_directories(Dependencies/include)

add_executable(OpenGL_CLion ${source_files})

#find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(OpenGL_CLion ${dep_dir}/GLFW/libglfw.so.3.3)
target_link_libraries(OpenGL_CLion ${dep_dir}/GLUT/libglut.so.3.12.0)
target_link_libraries(OpenGL_CLion OpenGL::GL)
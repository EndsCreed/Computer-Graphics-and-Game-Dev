cmake_minimum_required(VERSION 3.28)
project(OpenGL_CLion)

set(CMAKE_CXX_STANDARD 26)

include_directories(Dependencies/include)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(OpenGL_CLion main.cpp)

target_link_libraries(OpenGL_CLion /usr/lib64/libglfw.so.3.3)
target_link_libraries(OpenGL_CLion GLUT::GLUT)
target_link_libraries(OpenGL_CLion OpenGL::GL)
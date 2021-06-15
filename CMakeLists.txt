cmake_minimum_required(VERSION 3.19)
project(CGV_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(CGV_project main.cpp)
target_link_libraries(CGV_project -lfreeglut -lglew32 -lopengl32 -lglu32)

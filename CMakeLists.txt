project(container)
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(
        container
        src/linear_container.cpp
        src/main.cpp
        src/graph.cpp
        src/tree.cpp
)
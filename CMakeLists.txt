cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(projtmpl VERSION 1.0)
add_executable(projtmpl src/main.cpp)
target_include_directories(projtmpl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
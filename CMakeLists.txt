cmake_minimum_required(VERSION 3.22)
project(pozakres)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

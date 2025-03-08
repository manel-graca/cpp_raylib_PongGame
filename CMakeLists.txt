cmake_minimum_required(VERSION 3.31.6)
project(testgamerlib00 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)
add_executable(testgamerlib00 main.cpp)
target_link_libraries(testgamerlib00 PRIVATE raylib)
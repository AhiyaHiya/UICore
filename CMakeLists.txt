cmake_minimum_required(VERSION 3.28)
project(UICore VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(UICore src/UICore.cpp)

add_subdirectory(tests)

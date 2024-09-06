cmake_minimum_required(VERSION 3.28)
project(UICore VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(UICore "src/UICore.cpp")
target_include_directories(UICore PUBLIC "include")

add_subdirectory(tests)

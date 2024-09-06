cmake_minimum_required(VERSION 3.28)
project(UICore VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(resource_files "")
if(WIN32)
    set(resource_files
        "${CMAKE_CURRENT_LIST_DIR}/resources/resource.h"
        "${CMAKE_CURRENT_LIST_DIR}/resources/Resource.rc")
endif()

add_library(UICore STATIC
    "${resource_files}"
    "${CMAKE_CURRENT_LIST_DIR}/include/UICore/UICore.h"
    "${CMAKE_CURRENT_LIST_DIR}/src/UICore.cpp"
)
target_include_directories(UICore
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/resources"
)

if (DEFINED TESTING_ENABLED)
    add_subdirectory(tests)
endif()

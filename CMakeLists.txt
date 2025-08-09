cmake_minimum_required(VERSION 3.28...4.0)
project(MorgoUtil VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(MorgoUtil INTERFACE)
target_include_directories(MorgoUtil INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<INSTALL_INTERFACE:include>)
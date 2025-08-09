cmake_minimum_required(VERSION 3.28...4.0)
project(MorgoUtils VERSION 1.0.0
        LANGUAGES CXX)

add_library(MorgoUtils INTERFACE)
target_include_directories(MorgoUtils INTERFACE src)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

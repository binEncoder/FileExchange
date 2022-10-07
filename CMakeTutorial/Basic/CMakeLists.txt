cmake_minimum_required(VERSION 3.18.4)

# set the project name
project(DesignModel VERSION 1.0)

include_directories(./app/inc)
aux_source_directory(./app/src SRC_LIST)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(DesignModel ${SRC_LIST})


cmake_minimum_required(VERSION 3.18.4)

# set the project name
set(PROJECT_NAME DesignModel)
project(${PROJECT_NAME} VERSION 1.0)

include_directories(./app/inc)
aux_source_directory(./app/src SRC_LIST)

# specify the C/C++ compiler, or else the default compiler is /usr/lib64/ccache/c++
# set(CMAKE_C_COMPILER "/usr/bin/gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Manually specify the build map file information
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=${PROJECT_NAME}.map")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_MY_MATH "Use tutorial provided math implementation" ON)
option(USE_MY_FLASH "Use tutorial provided flash implementation" ON)

# related to MyMath library
if(USE_MY_MATH)
    add_definitions(-DENABLE_MY_MATH)
    add_subdirectory(./Library/MyMath)
    list(APPEND EXTRA_LIBS MyMath)
endif()

# related to MyFlash library
if(USE_MY_FLASH)
    add_definitions(-DENABLE_MY_FLASH)
    add_subdirectory(./Library/MyFlash)
    list(APPEND EXTRA_LIBS MyFlash)
endif()

# add the executable
add_executable(${PROJECT_NAME} ${SRC_LIST})

# link libraries and add included header path
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

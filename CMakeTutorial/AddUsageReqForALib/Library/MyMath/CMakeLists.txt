add_library(MyMath ./src/my_math.cpp)

# People who use this lib( consumers ) and build this lib( producer ) need to know the header file directory
target_include_directories(MyMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
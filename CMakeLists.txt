cmake_minimum_required(VERSION 2.8)
project(klargest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -Wextra -pedantic -O3 -Wno-long-long -fno-omit-frame-pointer")

include_directories(include)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
	src/parser_helper.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME})

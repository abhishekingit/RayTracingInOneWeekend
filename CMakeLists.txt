cmake_minimum_required(VERSION 3.27)

project(RayTracingInOneWeekend LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable (RayTracingInOneWeekend
	src/main.cpp
)


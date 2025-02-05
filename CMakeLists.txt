cmake_minimum_required(VERSION 3.27)

project(RayTracingInOneWeekend LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable (RayTracingInOneWeekend
	src/main.cpp
	src/vec3.h 
	src/color.h
	src/ray.h 
	src/hittableObject.h
	src/sphere.h
	src/hittableList.h
	src/commonConstants.h 
	src/interval.h 
	src/camera.h 
	src/material.h)


cmake_minimum_required(VERSION 2.8)

set(SOLUTION_NAME Sokit)
cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0005 NEW)

project(${SOLUTION_NAME})

message(STATUS "builder main start")

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "install prefix" FORCE)

# if(MSVC)
if(MSVC11 OR MSVC12 OR MSVC14)
	message(STATUS "Setting Visual Studio 2005+ option /MP to ${OGITOR_MSVC_ENABLE_MP}")
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DNOMINMAX)
endif(MSVC11 OR MSVC12 OR MSVC14)

add_subdirectory(Src)
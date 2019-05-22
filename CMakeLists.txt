cmake_minimum_required(VERSION 3.13)
project(ECS)

option(BUILD_DEBUG "Build the debug library" OFF)
option(BUILD_TESTS "Build the tests" ON)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Werror)
if(BUILD_DEBUG)
	add_compile_options(-g)
endif()

if(BUILD_TESTS)
	add_subdirectory("tests")
endif()

file(GLOB_RECURSE sources "src/*.cpp")
add_library(ecs ${sources})
target_include_directories(ecs PUBLIC "include")
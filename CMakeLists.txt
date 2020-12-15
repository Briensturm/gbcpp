cmake_minimum_required(VERSION 3.10)

enable_testing()

project(gbcpp)

#add glfw library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

#add OpenAL library
add_subdirectory(openal)

#add source
add_subdirectory(src)

#add tests
include_directories(src)
add_subdirectory(test)
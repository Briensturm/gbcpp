cmake_minimum_required(VERSION 3.11)

include(FetchContent)
enable_testing()

project(gbcpp)

#add glfw library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 0a49ef0a00baa3ab520ddc452f0e3b1e099c5589 #v3.3.3
)
FetchContent_MakeAvailable(glfw)

#add OpenAL library
FetchContent_Declare(
    openal_soft
    GIT_REPOSITORY https://github.com/kcat/openal-soft.git
    GIT_TAG openal-soft-1.21.0
)
FetchContent_MakeAvailable(openal_soft)

#add source
include_directories(src)
add_subdirectory(src)

#add tests
add_subdirectory(test)
include_directories(cpu)
include_directories(memory)
include_directories(sound)

add_subdirectory(cpu)
add_subdirectory(memory)
add_subdirectory(sound)

add_executable(gbcpp main.cpp)
target_link_libraries(gbcpp glfw)
include_directories(cpu)
include_directories(cart)
include_directories(ram)
include_directories(sound)
include_directories(video)

add_subdirectory(cpu)
add_subdirectory(cart)
add_subdirectory(ram)
add_subdirectory(sound)
add_subdirectory(video)

add_executable(gbcpp main.cpp)
target_link_libraries(gbcpp glfw)
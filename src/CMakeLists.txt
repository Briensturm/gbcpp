#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(gameboy CpuCore.cpp CpuCore.hpp)

add_subdirectory(sound)

add_executable(gbcpp main.cpp)
target_link_libraries(gbcpp glfw gameboy)
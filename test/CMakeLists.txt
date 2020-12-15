add_executable(test_gbcpp RegisterTests.cpp)
target_link_libraries(test_gbcpp gameboy)

add_test(RegisterTests test_gbcpp)
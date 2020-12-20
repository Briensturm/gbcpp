add_executable(test_gbcpp 
    register_tests.cpp
)

target_link_libraries(test_gbcpp cpu)

add_test(register_tests test_gbcpp)
add_executable(ram_tests 
    ram_tests.cpp
)
target_link_libraries(ram_tests ram)
add_test(ram_tests ram_tests)
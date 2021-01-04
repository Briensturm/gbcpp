add_executable(register_tests 
    register_tests.cpp
)
target_link_libraries(register_tests cpu)
add_test(register_tests register_tests)

add_executable(cpustate_tests 
    cpustate_tests.cpp
)
target_link_libraries(cpustate_tests cpu)
add_test(cpustate_tests cpustate_tests)

add_executable(cpucore_tests 
cpucore_tests.cpp
)
target_link_libraries(cpucore_tests cpu ram)
add_test(cpucore_tests cpucore_tests)

add_executable(instrdec_tests 
    instrdec_tests.cpp
)
target_link_libraries(instrdec_tests cpu)
add_test(instrdec_tests instrdec_tests)
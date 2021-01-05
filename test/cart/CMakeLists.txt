add_executable(mbc_tests 
    mbc_tests.cpp
)
target_link_libraries(mbc_tests cart)
add_test(mbc_tests mbc_tests)
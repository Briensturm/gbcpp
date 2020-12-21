#pragma once

#include <iostream>
#include <iomanip>
#include <functional>
#include <memory>
#include <string>
#include <stdexcept>

#include "mock.hpp"

auto fixtureReturnValue = 0;
std::string currentTestName;

#define HEX(x)                                             \
std::setw(2) << std::setfill('0') << std::hex << (int)( x )

#define TEST_FIXTURE_BEGIN(name)                               \
int main()                                                     \
{                                                              \
    std::cout << "Running testfixture: " << name << std::endl;                            

#define TEST_FIXTURE_END        \
    return fixtureReturnValue;  \
}

#define TEST(name)          \
    currentTestName = name; 

#define FAIL(message)                                             \
{                                                                 \
    fixtureReturnValue |= 1;                                      \
    std::cout << "\033[31mFailed test: " << currentTestName       \
    << " (" << __FILE__ << ")\033[0m" << std::endl;               \
    std::cout << "\033[31m" << message << "\033[0m" << std::endl; \
}

void ASSERT_TRUE(bool expression)
{
    if(!expression)
        FAIL("ASSERT_TRUE: Expression evaluated to false.");
}

void ASSERT_FALSE(bool expression)
{
    if(expression)
        FAIL("ASSERT_FALSE: Expression evaluated to true.");
}

template<typename T>
void ASSERT_EQUAL(const T& expected, const T& actual)
{
    if(expected != actual)                                                                                                                                                    
        FAIL("ASSERT_EQUAL: Arguments are not equal. Expected: " << expected << "; Actual: " << actual);
}

template<>
void ASSERT_EQUAL<uint8_t>(const uint8_t& expected, const uint8_t& actual)
{
    if(expected != actual)                                                                       
        FAIL("ASSERT_EQUAL: Arguments are not equal. Expected: 0x" << HEX(expected) << "; Actual: 0x" << HEX(actual));
}

template<>
void ASSERT_EQUAL<unsigned short>(const unsigned short& expected, const unsigned short& actual)
{
    if(expected != actual)                                                                        
        FAIL("ASSERT_EQUAL: Arguments are not equal. Expected: 0x" << HEX(expected) << "; Actual: 0x" << HEX(actual));
}

template<typename T>
void ASSERT_NOT_EQUAL(const T& expected, const T& actual)
{
    if(expected == actual)                                                                                                                                                    
        FAIL("ASSERT_NOT_EQUAL: Arguments are equal (" << expected << "), expected inequality.");
}

template<typename T>
void ASSERT_NOT_NULL(std::shared_ptr<T> ptr)
{
    if(ptr == nullptr)
        FAIL("ASSERT_NOT_NULL: Pointer is a nullptr, expected non-null ptr.");
}

template<typename T>
void ASSERT_NULL(std::shared_ptr<T> ptr)
{
    if(ptr != nullptr)
        FAIL("ASSERT_NULL: Pointer is non-null, expected a nullptr.");
}

template<typename exceptionType, typename F>
void ASSERT_THROWS(F&& lambda)
{
    auto exceptionThrown = false;
    try
    {
        lambda();
    }
    catch(const exceptionType exception)
    {
        exceptionThrown = true;
    }
    catch(...)
    {
        exceptionThrown = true;
        FAIL("ASSERT_THROWS: Unexpected exception was thrown.");
    }
    
    if(!exceptionThrown)
        FAIL("ASSERT_THROWS: No exception was thrown.");
}

template<typename F>
void ASSERT_DOES_NOT_THROW(F&& lambda)
{
    try
    {
        lambda();
    }
    catch(...)
    {
        FAIL("ASSERT_DOES_NOT_THROW: Unexpected exception was thrown.");
    }
}                              
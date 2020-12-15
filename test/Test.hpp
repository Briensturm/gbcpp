#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <stdexcept>

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

#define FAIL(message)                                       \
fixtureReturnValue |= 1;                                    \
std::cout << "\033[31mFailed test: " << currentTestName     \
<< " (" << __FILE__ << ")\033[0m" << std::endl;             \
std::cout << "\033[31m" << message << "\033[0m" << std::endl

#define ASSERT_TRUE(condition)                                         \
if(!(condition))                                                       \
{                                                                      \
    FAIL("(" << #condition << ") evaluated to false; expected: true"); \
}   

#define ASSERT_FALSE(condition)                                        \
if(condition)                                                          \
{                                                                      \
    FAIL("(" << #condition << ") evaluated to true; expected: false"); \
}  

template<typename T>
void ASSERT_EQUAL(const T& expected, const T& actual)
{
    if(expected != actual)                                                                
    {                                                                                     
        FAIL("Arguments are not equal. Expected: " << expected << "; Actual: " << actual);
    }
}

template<>
void ASSERT_EQUAL<uint8_t>(const uint8_t& expected, const uint8_t& actual)
{
    if(expected != actual)                                                                
    {         
        std::cout << "success!" << std::endl;                                                                            
        FAIL("Arguments are not equal. Expected: 0x" << HEX(expected) << "; Actual: 0x" << HEX(actual));
    }
}

template<>
void ASSERT_EQUAL<unsigned short>(const unsigned short& expected, const unsigned short& actual)
{
    if(expected != actual)                                                                
    {         
        std::cout << "success!" << std::endl;                                                                            
        FAIL("Arguments are not equal. Expected: 0x" << HEX(expected) << "; Actual: 0x" << HEX(actual));
    }
}

#define ASSERT_NOT_EQUAL(expected, actual)                                  \
if(expected == actual)                                                      \
{                                                                           \
    FAIL("Arguments are equal (" << expected << "), expected inequality."); \
}  

#define ASSERT_NOT_NULL(ptr)                               \
if(ptr == nullptr)                                         \
{                                                          \
    FAIL(#ptr << " is a nullptr, expected non-null ptr."); \
}

#define ASSERT_NULL(ptr)                             \
if(ptr != nullptr)                                   \
{                                                    \
    FAIL(#ptr << " is non-null, expected nullptr."); \
}

#define ASSERT_THROWS(exceptionType, code)                                \
auto exceptionThrown = false;                                             \
try                                                                       \
{                                                                         \
    code;                                                                 \
}                                                                         \
catch(const exceptionType exception)                                      \
{                                                                         \
    exceptionThrown = true;                                               \
}                                                                         \
catch(...)                                                                \
{                                                                         \
    exceptionThrown = true;                                               \
    FAIL("Unexpected exception was thrown. Expected " << #exceptionType); \
}                                                                         \
if(!exceptionThrown)                                                      \
{                                                                         \
    FAIL("No exception was thrown. Expected " << #exceptionType);         \
}

#define ASSERT_DOES_NOT_THROW(code)                   \
try                                                   \
{                                                     \
    code;                                             \
}                                                     \
catch(...)                                            \
{                                                     \
    FAIL(#code << " threw an unexpected exception."); \
}                                             
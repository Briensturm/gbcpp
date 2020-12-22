#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>

template<typename realType, typename mockType>
std::shared_ptr<realType> GET_OBJECT(std::shared_ptr<mockType> mockPtr)
{
    return std::static_pointer_cast<realType>(mockPtr);
}

template<typename mockType>
std::shared_ptr<mockType> CREATE_MOCK()
{
    return std::make_shared<mockType>();
}

template<typename mockType, typename realType>
std::shared_ptr<realType> MOCK_OF()
{
    return std::static_pointer_cast<realType>(std::make_shared<mockType>());
}

#define MOCK_METHOD(methodName)       \
public:                               \
    void methodName() {               \
        void_##methodName##_InvokeCount++;   \
    }                                 \
    int void_##methodName##_InvokeCount = 0; 

#define MOCK_METHOD_RET(returnType, methodName)                              \
public:                                                                         \
    returnType methodName() {                                                   \
        returnType##_##methodName##_InvokeCount++;                                             \
        return *returnType##_##methodName##_ReturnValue;                                       \
    }                                                                           \
    void returnType##_##methodName##_SetReturnValue(std::shared_ptr<returnType> returnValue) { \
        returnType##_##methodName##_ReturnValue = returnValue;                                 \
    }                                                                           \
    void returnType##_##methodName##_SetReturnValue(returnType returnValue) {                  \
        returnType##_##methodName##_ReturnValue = std::make_shared<returnType>(returnValue);   \
    }                                                                           \
    int returnType##_##methodName##_InvokeCount = 0;                                           \
private:                                                                        \
    std::shared_ptr<returnType> returnType##_##methodName##_ReturnValue = nullptr;

#define MOCK_METHOD_P(methodName, paramType)       \
public:                               \
    void methodName(paramType param) {               \
            void_##methodName##_##paramType##_Invokes.push_back(param); \
    }                                \
    int GetInvokeCount_void_##methodName##_##paramType(paramType param)    { \
        return (int)std::count(void_##methodName##_##paramType##_Invokes.begin(), \
        void_##methodName##_##paramType##_Invokes.end(), param); \
    } \
    std::vector<paramType> \
    void_##methodName##_##paramType##_Invokes = std::vector<paramType>();

#define MOCK_METHOD_RET_P(returnType, methodName, paramType)       \
public:                               \
    returnType methodName(paramType param) {               \
            returnType##_##methodName##_##paramType##_Invokes.push_back(param); \
            return *returnType##_##methodName##_##paramType##_ReturnValues.at(param); \
    }                                \
    void returnType##_##methodName##_##paramType##_SetReturnValue(paramType param, std::shared_ptr<returnType> returnValue) { \
        returnType##_##methodName##_##paramType##_ReturnValues[param] = returnValue;\
    }                                                                           \
    void returnType##_##methodName##_##paramType##_SetReturnValue(paramType param, returnType returnValue) {                  \
        returnType##_##methodName##_##paramType##_ReturnValues[param] = std::make_shared<returnType>(returnValue);   \
    }  \
    int GetInvokeCount_##returnType##_##methodName##_##paramType(paramType param)    { \
        return (int)std::count(returnType##_##methodName##_##paramType##_Invokes.begin(), \
        returnType##_##methodName##_##paramType##_Invokes.end(), param); \
    } \
    std::vector<paramType> returnType##_##methodName##_##paramType##_Invokes = std::vector<paramType>(); \
    std::unordered_map<paramType, std::shared_ptr<returnType>> returnType##_##methodName##_##paramType##_ReturnValues = std::unordered_map<paramType, std::shared_ptr<returnType>>();

#define MOCK_METHOD_2P(methodName, paramType1, paramType2)       \
public:                               \
    void methodName(paramType1 param1, paramType2 param2) {               \
        auto params = std::pair<paramType1, paramType2>(param1, param2); \
        void_##methodName##_##paramType1##_##paramType2##_Invokes.push_back(params); \
    }                                \
    int GetInvokeCount_void_##methodName##_##paramType1##_##paramType2(paramType1 param1, paramType2 param2)    { \
        auto params = std::pair<paramType1, paramType2>(param1, param2); \
        return (int)std::count(void_##methodName##_##paramType1##_##paramType2##_Invokes.begin(), \
        void_##methodName##_##paramType1##_##paramType2##_Invokes.end(), params); \
    } \
    std::vector<std::pair<paramType1, paramType2>> \
    void_##methodName##_##paramType1##_##paramType2##_Invokes = std::vector<std::pair<paramType1, paramType2>>(); 

#define MOCK_METHOD_RET_2P(returnType, methodName, paramType1, paramType2) \
public: \
    returnType methodName(paramType1 param1, paramType2 param2) { \
        auto params = std::pair<paramType1, paramType2>(param1, param2); \
        returnType##_##methodName##_##paramType1##_##paramType2##_Invokes.push_back(params); \
        return *returnType##_##methodName##_##paramType1##_##paramType2##_ReturnValues.at(params); \
    } \
    void returnType##_##methodName##_##paramType1##_##paramType2##_SetReturnValue(paramType1 param1, paramType2 param2, std::shared_ptr<returnType> returnValue) { \
        auto params = std::pair<paramType1, paramType2>(param1, param2); \
        returnType##_##methodName##_##paramType1##_##paramType2##_ReturnValues[params] = returnValue;\
    } \
    void returnType##_##methodName##_##paramType1##_##paramType2##_SetReturnValue(paramType1 param1, paramType2 param2, returnType returnValue) { \
        auto params = std::pair<paramType1, paramType2>(param1, param2); \
        returnType##_##methodName##_##paramType1##_##paramType2##_ReturnValues[params] = std::make_shared<returnType>(returnValue); \
    }                                                                        \
    int GetInvokeCount_##returnType##_##methodName##_##paramType1##_##paramType2(paramType1 param1, paramType2 param2)    { \
        auto params = std::pair<paramType1, paramType2>(param1, param2); \
        return (int)std::count(returnType##_##methodName##_##paramType1##_##paramType2##_Invokes.begin(), \
        returnType##_##methodName##_##paramType1##_##paramType2##_Invokes.end(), params); \
    } \
    std::vector<std::pair<paramType1, paramType2>> returnType##_##methodName##_##paramType1##_##paramType2##_Invokes = std::vector<std::pair<paramType1, paramType2>>(); \
    std::unordered_map<std::pair<paramType1, paramType2>, std::shared_ptr<returnType>> returnType##_##methodName##_##paramType1##_##paramType2##_ReturnValues = std::unordered_map<std::pair<paramType1, paramType2>, std::shared_ptr<returnType>>();

#define ONCE == 1
#define TIMES(count) == count
#define NEVER == 0
#define AT_LEAST(count) >= count

#define VERIFY(mock, methodName, times) \
if(!(mock->void_##methodName##_InvokeCount times)) \
    FAIL("Expected " << #methodName << "() to be called " << #times << \
    ", but was: " << mock->void_##methodName##_InvokeCount);

#define VERIFY_RET(mock, returnType, methodName, times) \
if(!(mock->returnType##_##methodName##_InvokeCount times)) \
    FAIL("Expected " << #returnType << " " << #methodName << "() to be called " << #times << \
    ", but was: " << mock->returnType##_##methodName##_InvokeCount);

#define VERIFY_P(mock, methodName, paramType, paramValue, times) \
if(!(mock->GetInvokeCount_void_##methodName##_##paramType(paramValue) times)) \
    FAIL("Expected " << #methodName << "(" << #paramType << ") to be called " << #times << \
    ", but was: " << mock->GetInvokeCount_void_##methodName##_##paramType(paramValue));

#define VERIFY_RET_P(mock, returnType, methodName, paramType, paramValue, times) \
if(!(mock->GetInvokeCount_##returnType##_##methodName##_##paramType(paramValue) times)) \
    FAIL("Expected " << #returnType << " " << #methodName << "(" << #paramType << ") to be called " << #times << \
    ", but was: " << mock->GetInvokeCount_##returnType##_##methodName##_##paramType(paramValue));

#define VERIFY_2P(mock, methodName, paramType1, paramValue1, paramType2, paramValue2, times) \
if(!(mock->GetInvokeCount_void_##methodName##_##paramType1##_##paramType2(paramValue1, paramValue2) times)) \
    FAIL("Expected " << #methodName << "(" << #paramType1 << ", " << #paramType2 << ") to be called " << #times << \
    ", but was: " << mock->GetInvokeCount_void_##methodName##_##paramType1##_##paramType2(paramValue1, paramValue2));

#define VERIFY_RET_2P(mock, returnType, methodName, paramType1, paramValue1, paramType2, paramValue2, times) \
if(!(mock->GetInvokeCount_##returnType##_##methodName##_##paramType1##_##paramType2(paramValue1, paramValue2) times)) \
    FAIL("Expected " << #returnType << " " << #methodName << "(" << #paramType1 << ", " << #paramType2 << ") to be called " << #times << \
    ", but was: " << mock->GetInvokeCount_##returnType##_##methodName##_##paramType1##_##paramType2(paramValue1, paramValue2));

namespace std 
{
    template<typename type1, typename type2>
    struct hash<std::pair<type1, type2>>
    {
        std::size_t operator()(const std::pair<type1, type2>& p) const
        {
            return (std::hash<int>()(p.first)) 
                 ^ (std::hash<int>()(p.second) << 1);
        }
    };
}
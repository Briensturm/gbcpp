#pragma once

#define MOCK_METHOD(methodName) \
public: \
    void methodName() {\
        methodName##_InvokeCount++; \
    } \
    int methodName##_InvokeCount;

#define MOCK_METHOD_RETURN(methodName, returnValue) \
public: \
    void methodName() {\
        methodName##_InvokeCount++; \
        return returnValue; \
    } \
    int methodName##_InvokeCount;

#define VERIFY_INVOKE_COUNT(mock, methodName, invokeCount) \
if(mock->methodName##_InvokeCount != invokeCount) {\
    FAIL("Expected " << #methodName << "() to be called " << invokeCount \
    << " time(s), but was: " << mock->methodName##_InvokeCount); \
}

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
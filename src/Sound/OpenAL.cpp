#include "OpenAL.hpp"

#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

void OpenAL::DoStuffWithOpenAL()
{
    auto alDevice = alcOpenDevice("mydevice");
}
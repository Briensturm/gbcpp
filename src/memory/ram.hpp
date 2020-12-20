#pragma once

#include <memory>

class RandomAccessMemory
{
    public:
        void DoStuff();
};

using RamPtr = std::shared_ptr<RandomAccessMemory>;
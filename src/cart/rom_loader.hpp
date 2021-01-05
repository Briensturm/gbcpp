#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "gbcpp.hpp"

class RomLoader
{
    public:
        RomLoader(std::string filePath) : _filePath(filePath) {}

        std::vector<byte> LoadRom()
        {
            std::ifstream stream(_filePath, std::ios::in | std::ios::binary);
            return std::vector<byte>((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        }

    private:
        const std::string _filePath;
};

using RomLoaderPtr = std::shared_ptr<RomLoader>;

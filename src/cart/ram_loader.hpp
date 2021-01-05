#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "gbcpp.hpp"

class RamLoader
{
    public:
        RamLoader(std::string filePath) : _filePath(filePath) {}

        std::vector<byte> TryLoadRam() const
        {
            std::ifstream stream(_filePath, std::ios::in | std::ios::binary);
            if(!stream.good())
                return std::vector<byte>();

            return std::vector<byte>((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        }

        void SaveRam(std::vector<byte> ramData) const
        {
            std::ofstream file(_filePath, std::ios::out | std::ios::binary); 
            file.write((const char*)ramData.data(), ramData.size());
        }

    private:
        const std::string _filePath;   
};

using RamLoaderPtr = std::shared_ptr<RamLoader>;

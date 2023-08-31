// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class BwInputStream {
public:
    BwInputStream(const std::filesystem::path& path) {
        _stream.open(path, std::ifstream::binary | std::ifstream::in);
    }

    ~BwInputStream() = default;

    template<typename T>
    T Get()
    {
        T buf;
        _stream.read(reinterpret_cast<char*>(&buf), sizeof(buf));
        return buf;
    }

    std::string GetString()
    {
        std::string str;
        std::getline(_stream, str, '\0');
        return str;
    }

    std::string GetString(uint32_t len) {
        std::string str;
        if (len) {
            str.resize(len);
            _stream.read(reinterpret_cast<char*>(str.data()), len);
        }

        return str;
    }

    void GetBytes(std::vector<uint8_t>& buffer, uint32_t len) {
        buffer.resize(len);
        _stream.read(reinterpret_cast<char*>(buffer.data()), len);
    }

private:
    std::ifstream _stream;
};

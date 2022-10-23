// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <algorithm>
#include <vector>
#include <string>

class Vector{
public:

    template <typename T>
    static void RemoveDuplicates(std::vector<T>& vec)
    {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    }

    static void PtrToVec(std::vector<uint8_t>& vec, void* val) {
        auto val_converted = reinterpret_cast<size_t>(val);
        for (size_t i = 0; i < sizeof(val_converted); i++){
            uint8_t byte = (val_converted >> (i * 8)) & 0xFF;
            vec.push_back(byte);
        }
    }

    static void* VecToPtr(std::vector<uint8_t>& vec) {
        void* ptr = nullptr;
        memcpy(&ptr, vec.data(), sizeof(ptr));
        return ptr;
    }
};

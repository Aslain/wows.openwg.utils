// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

//
// Includes
//

// stdlib
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>



//
// Class
//

namespace OpenWG::Utils::Common {
    namespace Vector {

        template<typename T>
        inline bool Contains(const std::vector<T> &vec, const T &val) {
            return std::find(vec.begin(), vec.end(), val) != vec.end();
        }

        template<typename T>
        inline void RemoveDuplicates(std::vector<T> &vec) {
            std::sort(vec.begin(), vec.end());
            vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        }

        inline void PtrToVec(std::vector<uint8_t> &vec, void *val) {
            auto val_converted = reinterpret_cast<size_t>(val);
            for (size_t i = 0; i < sizeof(val_converted); i++) {
                uint8_t byte = (val_converted >> (i * 8)) & 0xFF;
                vec.push_back(byte);
            }
        }

        inline void *VecToPtr(std::vector<uint8_t> &vec) {
            void *ptr = nullptr;
            std::memcpy(&ptr, vec.data(), sizeof(ptr));
            return ptr;
        }
    }
}
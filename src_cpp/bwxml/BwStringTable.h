// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <vector>
#include <string>

#include "common/encoding.h"
#include "bwxml/BwInputStream.h"

class BwStringTable {
public:
    BwStringTable() = default;

    std::string Get(uint32_t idx)
    {
        return _data[idx];
    }

    std::wstring GetW(uint32_t idx)
    {
        return Encoding::utf8_to_wstring(Get(idx));
    }

    bool Read(BwInputStream& stream) {
        _data.clear();

        while (true) {
            std::string str = stream.GetString();
            if (str.size() == 0) {
                break;
            }

            _data.push_back(str);
        }

        return true;
    }

private:
    std::vector<std::string> _data;
};

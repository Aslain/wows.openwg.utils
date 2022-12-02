// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include "bwxml/BwInputStream.h"
#include "bwxml/BwPackedSection.h"
#include "bwxml/BwStringTable.h"

class BwXml {
public:
    BwXml() = default;
    ~BwXml() = default;

    bool Read(const wchar_t* input_filename);
    bool SaveXml(const wchar_t* output_filename);

private:

    bool readHeader(BwInputStream& stream);

    BwPackedSection _root_section;
    BwStringTable _string_table;

    static constexpr uint32_t magic_expected = 0x62A14E45;
    static constexpr uint8_t  version_supported = 0;
};

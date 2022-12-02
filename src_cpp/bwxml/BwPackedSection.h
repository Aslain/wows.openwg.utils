// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include "pugixml.hpp"

#include "bwxml/BwInputStream.h"
#include "bwxml/BwDataElement.h"
#include "bwxml/BwStringTable.h"

class BwPackedSection {
public:
    BwPackedSection() = default;
    BwPackedSection(BwInputStream& stream);
    ~BwPackedSection() = default;

    bool Read(BwInputStream& stream);
    void SaveXml(pugi::xml_node&, BwStringTable& stringTable);

private:
    BwDataElement _data;
    std::vector<std::pair<uint16_t, BwDataElement>> _children;
};
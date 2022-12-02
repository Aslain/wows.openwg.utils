// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "bwxml/BwPackedSection.h"

BwPackedSection::BwPackedSection(BwInputStream& stream)
{
    Read(stream);
}

bool BwPackedSection::Read(BwInputStream& stream)
{
    uint16_t children_count = stream.Get<uint16_t>();
    auto typeoff = stream.Get<BwDataDescriptor>();

    std::vector<std::pair<uint16_t, BwDataDescriptor>> children;
    children.reserve(children_count);
    for (int i = 0; i < children_count; ++i)
    {
        auto child_nameidx = stream.Get<uint16_t>();
        auto child_typeoffset = stream.Get<BwDataDescriptor>();
        children.emplace_back(child_nameidx, child_typeoffset);
    }

    _data = BwDataElement(stream, typeoff, 0);
    int prev_offset = typeoff.GetDataOffset();

    for (auto& child : children) {
        auto child_data = BwDataElement(stream, child.second, prev_offset);
        _children.emplace_back(child.first, child_data);
        prev_offset = child.second.GetDataOffset();
    }

    return true;
}

void BwPackedSection::SaveXml(pugi::xml_node& node, BwStringTable& stringTable)
{
    _data.SaveXml(node, stringTable);

    for (auto& child : _children) {
        auto child_node = node.append_child(stringTable.GetW(child.first).c_str());
        child.second.SaveXml(child_node, stringTable);
    }
}

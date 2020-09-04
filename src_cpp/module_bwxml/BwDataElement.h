#pragma once

#include "pugixml.hpp"

#include "module_bwxml/BwInputStream.h"
#include "module_bwxml/BwDataDescriptor.h"
#include "module_bwxml/BwStringTable.h"


class BwDataElement {
public:
	BwDataElement() = default;
	~BwDataElement();
	BwDataElement(BwInputStream& stream, BwDataDescriptor typeoff, int32_t element_startoff);

	void SaveXml(pugi::xml_node& node, BwStringTable& stringTable);

private:
	BwDataType _type;
	std::vector<uint8_t> _data;
};
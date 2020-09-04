#pragma once

#include "module_bwxml/BwInputStream.h"
#include "module_bwxml/BwPackedSection.h"
#include "module_bwxml/BwStringTable.h"

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
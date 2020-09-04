#include "pugixml.hpp"

#include "module_bwxml/BwXml.h"

bool BwXml::Read(const wchar_t* input_filename)
{
	BwInputStream stream(input_filename);

	if (!readHeader(stream)) {
		return false;
	}

	if (!_string_table.Read(stream)) {
		return false;
	}

	if (!_root_section.Read(stream)) {
		return false;
	}

	return true;
}

bool BwXml::SaveXml(const wchar_t* output_filename)
{
	pugi::xml_document doc;
	pugi::xml_node node = doc.append_child(L"root");

	_root_section.SaveXml(node, _string_table);

	doc.save(std::ofstream(output_filename));
	return true;
}

bool BwXml::readHeader(BwInputStream& stream) {
	auto magic = stream.Get<uint32_t>();
	auto version = stream.Get<uint8_t>();

	if (magic != magic_expected) {
		return false;
	}

	if (version != version_supported) {
		return false;
	}

	return true;
}

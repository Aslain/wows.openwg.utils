#pragma once

#include <cstdint>

enum class BwDataType: uint32_t
{
	TYPE_DATA_SECTION   = 0x00000000,
	TYPE_STRING         = 0x10000000,
	TYPE_INT            = 0x20000000,
	TYPE_FLOAT          = 0x30000000,
	TYPE_BOOL           = 0x40000000,
	TYPE_BLOB           = 0x50000000,
	TYPE_ENCRYPTED_BLOB = 0x60000000,
	TYPE_ERROR          = 0x70000000,
};

#pragma pack(push, 1)
class BwDataDescriptor {
public:
	BwDataDescriptor() = default;
	~BwDataDescriptor() = default;

	BwDataType GetDataType() {
		return static_cast<BwDataType>(_data & MASK_SECTION_TYPE);
	}

	uint32_t GetDataOffset() {
		return _data & MASK_SECTION_OFFSET;
	}

private:
	uint32_t _data = 0;

	static constexpr uint32_t MASK_SECTION_OFFSET = 0x0fffffff;
	static constexpr uint32_t MASK_SECTION_TYPE = ~MASK_SECTION_OFFSET;
};
#pragma pack(pop)

static_assert(sizeof(BwDataDescriptor) == 4);

#include <cassert>

#include "common/encoding.h"
#include "common/string.h"
#include "common/vector.h"

#include "module_bwxml/BwDataElement.h"
#include "module_bwxml/BwPackedSection.h"

BwDataElement::~BwDataElement()
{
}

BwDataElement::BwDataElement(BwInputStream& stream, BwDataDescriptor typeoff, int32_t element_startoff)
{
    int32_t element_size = typeoff.GetDataOffset() - element_startoff;
    assert(element_size >= 0);

    _type = typeoff.GetDataType();
    switch (_type)
    {
        case BwDataType::TYPE_DATA_SECTION: {
            Vector::PtrToVec(_data, new BwPackedSection(stream));
            break;
        }
        default:
            stream.GetBytes(_data, element_size);
            break;
    }
}

void BwDataElement::SaveXml(pugi::xml_node& node, BwStringTable& stringTable)
{
    switch (_type) {
        case BwDataType::TYPE_DATA_SECTION: {
            BwPackedSection* ptr = nullptr;
            memcpy(&ptr, _data.data(), sizeof(ptr));
            ptr->SaveXml(node, stringTable);
            break;
        }

        case BwDataType::TYPE_STRING: {
            if (_data.size() > 0) {
                node.append_child(pugi::node_pcdata).set_value(Encoding::utf8_to_wstring(std::string(_data.begin(), _data.end())).c_str());
            }
            break;
        }

        case BwDataType::TYPE_INT: {
            node.append_child(pugi::node_pcdata).set_value(String::VecToWstring(_data).c_str());
            break;
        }

        case BwDataType::TYPE_FLOAT: {
            assert(false, "Unsupported");
            break;
        }

        case BwDataType::TYPE_BOOL: {
            std::wstring str = L"false";
            if (_data.size() > 0 && _data[0] != 0) {
                str = L"true";
            }
            node.append_child(pugi::node_pcdata).set_value(str.c_str());
            break;
        }

        case BwDataType::TYPE_BLOB: {
            node.append_child(pugi::node_pcdata).set_value(Encoding::vec_to_base64w(_data).c_str());
            break;
        }

        case BwDataType::TYPE_ENCRYPTED_BLOB:
        case BwDataType::TYPE_ERROR:
        default: {
            assert(false, "Unsupported");
            break;
        }
    }
}
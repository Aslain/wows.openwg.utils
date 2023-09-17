//
// Includes
//

#include "wwise_bank_section_header.h"



//
// Implementation
//

namespace OpenWG::Utils::WWISE {

    SectionHeader::SectionHeader(std::fstream &stream) {
        Read(stream);
    }

    bool SectionHeader::Read(std::fstream &stream) {
        m_offset = stream.tellg();
        stream.read(reinterpret_cast<char *>(&m_bank_type), sizeof(m_bank_type));
        stream.read(reinterpret_cast<char *>(&m_length), sizeof(m_length));
        if (stream.fail()) {
            return false;
        }
        return true;
    }

    bool SectionHeader::Read(std::fstream &stream, size_t offset) {
        stream.seekg(offset, std::ios::beg);
        return Read(stream);
    }

    uint32_t SectionHeader::GetLength() const {
        return m_length;
    }

    size_t SectionHeader::GetOffsetSection() const {
        return m_offset;
    }

    size_t SectionHeader::GetOffsetData() const {
        return GetOffsetSection() + sizeof(m_bank_type) + sizeof(m_length);
    }

    SectionType SectionHeader::GetType() const {
        return m_bank_type;
    }


}

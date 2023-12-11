#pragma once

//
// Includes
//

// stdlib
#include <cstdint>
#include <fstream>

// OpenWG
#include "wwise_bank_section_type.h"



//
// Public
//


namespace OpenWG::Utils::WWISE {

    class SectionHeader {
    public:
        SectionHeader() = default;
        explicit SectionHeader(std::fstream& stream);
        bool Read(std::fstream& stream);
        bool Read(std::fstream& stream, size_t offset);

        [[nodiscard]] uint32_t GetLength() const;
        [[nodiscard]] size_t GetOffsetSection() const;
        [[nodiscard]] size_t GetOffsetData() const;

        [[nodiscard]] SectionType GetType() const;

    protected:
        // bank fields
        SectionType m_bank_type{};
        uint32_t m_length{};

        // offset
        size_t m_offset{};
    };
}

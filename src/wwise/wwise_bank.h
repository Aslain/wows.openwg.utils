#pragma once

//
// Includes
//

// stdlib
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>

// openwg
#include "common/api_common.h"
#include "wwise_bank_section_header.h"
#include "wwise_bank_section_bkhd.h"
#include "wwise_bank_section_type.h"



//
// Public
//

namespace OpenWG::Utils::WWISE {
    class Bank {
    public:
        bool Read(const std::filesystem::path &path);

        [[nodiscard]] SectionBKHD& BKHD();

        bool Save();
        bool Save(const std::filesystem::path& path);

    private:
        std::filesystem::path m_path{};
        std::map<SectionType, SectionHeader> m_sections{};
        SectionBKHD m_section_bkhd{};
    };
}

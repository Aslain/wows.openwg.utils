#pragma once

//
// Includes
//

// stdlib
#include <memory>

// OpenWG
#include "common/api_common.h"
#include "wwise_bank_section_header.h"
#include "wwise_license.h"


//
// Public
//

namespace OpenWG::Utils::WWISE {

    class SectionBKHD {
    public:
        SectionBKHD() = default;
        SectionBKHD(std::fstream& stream, const SectionHeader& sectionBase);

    public:
        bool Read(std::fstream& stream, const SectionHeader& sectionBase);
        bool Write(std::fstream& stream, const SectionHeader& sectionBase);

        bool Decrypt(const License& license);
        bool Encrypt(const License& license);

        [[nodiscard]] uint32_t GetVersion() const;
        [[nodiscard]] uint32_t GetBankId() const;
        [[nodiscard]] uint32_t GetLanguageId() const;
        [[nodiscard]] uint16_t GetAlignment() const;
        [[nodiscard]] uint16_t GetDeviceAllocated() const;
        [[nodiscard]] uint32_t GetProjectId() const;

        [[nodiscard]] bool IsDecrypted() const;

        void SetBankId(const std::string& str);
        void SetProjectId(uint32_t value);

    private:
        uint32_t dwBankGeneratorVersion;
        uint32_t dwSoundBankID;
        uint32_t dwLanguageID;
        uint16_t uAlignment;
        uint16_t bDeviceAllocated;
        uint32_t dwProjectID;
    };
}


// license
//   - wg: 97b2f5d2 |
//
// Includes
//

#include "wwise_bank_section_bkhd.h"
#include "wwise_utils.h"


//
// Implementation
//

namespace OpenWG::Utils::WWISE {
    SectionBKHD::SectionBKHD(std::fstream& stream, const SectionHeader& sectionBase) {
        Read(stream, sectionBase);
    }

    bool SectionBKHD::Read(std::fstream& stream, const SectionHeader& sectionBase) {
        stream.seekg(sectionBase.GetOffsetData(), std::ios::beg);
        stream.read(reinterpret_cast<char *>(&dwBankGeneratorVersion), sizeof(dwBankGeneratorVersion));
        stream.read(reinterpret_cast<char *>(&dwSoundBankID), sizeof(dwSoundBankID));
        stream.read(reinterpret_cast<char *>(&dwLanguageID), sizeof(dwLanguageID));
        stream.read(reinterpret_cast<char *>(&uAlignment), sizeof(uAlignment));
        stream.read(reinterpret_cast<char *>(&bDeviceAllocated), sizeof(bDeviceAllocated));
        stream.read(reinterpret_cast<char *>(&dwProjectID), sizeof(dwProjectID));
        if (stream.fail()) {
            return false;
        }
        return true;
    }

    uint32_t SectionBKHD::GetVersion() const {
        return dwBankGeneratorVersion;
    }

    uint32_t SectionBKHD::GetBankId() const {
        return dwSoundBankID;
    }

    void SectionBKHD::SetBankId(const std::string &str) {
        FNVHash32 hash{};
        hash.Compute(str.data(), str.size());
        dwSoundBankID = hash.Get();
    }

    void SectionBKHD::SetProjectId(uint32_t value) {
        dwProjectID = value;
    }

    uint32_t SectionBKHD::GetLanguageId() const {
        return dwLanguageID;
    }

    uint32_t SectionBKHD::GetProjectId() const {
        return dwProjectID;
    }

    bool SectionBKHD::Decrypt(const License &license) {
        if ((dwBankGeneratorVersion ^ license.m_key[0]) != 135  //v2019.2
            && (dwBankGeneratorVersion ^ license.m_key[0]) != 150) { //v2023.1
            return false;
        }

        dwBankGeneratorVersion ^= license.m_key[0];
        dwSoundBankID ^= license.m_key[1];
        dwLanguageID ^= license.m_key[2];
        uAlignment ^= license.m_key[3] & ((1<<16)-1);
        bDeviceAllocated = ((bDeviceAllocated << 16) ^ license.m_key[3]) >> 16;

        return true;
    }

    bool SectionBKHD::Encrypt(const License &license) {
        if(!IsDecrypted()) {
            return false;
        }

        dwBankGeneratorVersion ^= license.m_key[0];
        dwSoundBankID ^= license.m_key[1];
        dwLanguageID ^= license.m_key[2];
        uAlignment ^= license.m_key[3] & ((1<<16)-1);
        bDeviceAllocated = ((bDeviceAllocated << 16) ^ license.m_key[3]) >> 16;
        return true;
    }

    uint16_t SectionBKHD::GetAlignment() const {
        return uAlignment;
    }

    uint16_t SectionBKHD::GetDeviceAllocated() const {
        return bDeviceAllocated;
    }

    bool SectionBKHD::Write(std::fstream &stream, const SectionHeader &sectionBase) {
        stream.seekg(sectionBase.GetOffsetData(), std::ios::beg);
        stream.write(reinterpret_cast<char *>(&dwBankGeneratorVersion), sizeof(dwBankGeneratorVersion));
        stream.write(reinterpret_cast<char *>(&dwSoundBankID), sizeof(dwSoundBankID));
        stream.write(reinterpret_cast<char *>(&dwLanguageID), sizeof(dwLanguageID));
        stream.write(reinterpret_cast<char *>(&uAlignment), sizeof(uAlignment));
        stream.write(reinterpret_cast<char *>(&bDeviceAllocated), sizeof(bDeviceAllocated));
        stream.write(reinterpret_cast<char *>(&dwProjectID), sizeof(dwProjectID));
        if (stream.fail()) {
            return false;
        }
        return true;
    }

    bool SectionBKHD::IsDecrypted() const {
        return dwBankGeneratorVersion == 0x87;
    }
}

//
// Includes
//

// stdlib


#include "wwise_bank.h"



//
// Implementation
//

namespace OpenWG::Utils::WWISE {

    bool Bank::Read(const std::filesystem::path &path) {
        if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
            return false;
        }

        std::fstream m_stream{};
        m_stream.open(path, std::ios::binary | std::ios::in | std::ios::out);
        if (m_stream.fail()) {
            return false;
        }

        while (true) {
            SectionHeader section{};
            if (!section.Read(m_stream)) {
                break;
            }
            m_sections[section.GetType()] = section;
            m_stream.seekg(section.GetLength(), std::ios::cur);
        }

        m_stream.clear();
        m_stream.seekg(0, std::ios::beg);

        m_section_bkhd = SectionBKHD(m_stream, m_sections[SectionType::BKHD]);

        m_path = path;
        return true;
    }

    SectionBKHD &Bank::BKHD() {
        return m_section_bkhd;
    }

    bool Bank::Save() {
        return Save(m_path);
    }

    bool Bank::Save(const std::filesystem::path &path) {
        if (path != m_path) {
            if (!std::filesystem::copy_file(m_path, path)) {
                return false;
            }
        }

        std::fstream stream{};
        stream.open(path, std::ios::binary | std::ios::in | std::ios::out);

        // save bkhd
        if(!BKHD().Write(stream, m_sections[SectionType::BKHD])) {
            return false;
        }

        stream.close();
        return true;
    }
}

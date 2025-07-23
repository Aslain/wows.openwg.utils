#include "string/string.h"
#include "wot/client_version.h"

namespace OpenWG::Utils::WoT {

    ClientVersion::ClientVersion(const std::wstring& str)
    {
        Set(str);
    }

    const std::wstring& ClientVersion::Get() const
    {
        return m_raw;
    }

    void ClientVersion::Set(const std::wstring& str)
    {
        m_raw = str;
        m_components.clear();
        for (const auto& tok : String::Split(m_raw, L'.')) {
            m_components.push_back(std::stoi(tok));
        }
    }

    std::strong_ordering ClientVersion::operator<=>(const ClientVersion& other) const
    {
        for (size_t idx = 0; idx < std::min(m_components.size(), other.m_components.size()); idx++) {
            auto r = m_components[idx] <=> other.m_components[idx];
            if (r != std::strong_ordering::equal) {
                return r;
            }
        }

        return std::strong_ordering::equal;
    }
}
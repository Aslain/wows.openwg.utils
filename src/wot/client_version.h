#pragma once

#include <string>
#include <vector>

namespace OpenWG::Utils::WoT {

    class ClientVersion {
    public:
        ClientVersion() = default;
        ClientVersion(const std::wstring& str);

        [[nodiscard]] const std::wstring& Get() const;
        void Set(const std::wstring& str);

        std::strong_ordering operator <=> (const ClientVersion& other) const;

    private:
        std::wstring m_raw;
        std::vector<int> m_components;
    };

}
#pragma once

// stdlib
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

// pugixml
#include <pugixml.hpp>


namespace OpenWG::Utils::XML {
    class XML {
    public:
        explicit XML(const std::filesystem::path& path);
        ~XML();

        bool AddKey(const std::wstring& path, const std::wstring& name, const std::wstring& value);

        bool ContainsKey(const std::wstring& path);
        bool ContainsKey(const std::wstring& path, const std::wstring& value);

        bool Save(const std::filesystem::path& path);

    private:
        pugi::xml_document m_doc;
    };
}

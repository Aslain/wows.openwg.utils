#pragma once

#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>

namespace OpenWG::Utils::JSON {
    class Json {
    public:
        Json(const std::filesystem::path& path);
        ~Json();

        bool SetBool(const std::wstring& path, bool value);

        bool Save();

    private:
        std::filesystem::path m_path;
        nlohmann::json m_json;
    };
}

#pragma once

#include "common/encoding.h"
#include <filesystem>
#include <stdint.h>
#include <string>

#include <json/json.h>

namespace OpenWG::Utils::JSON {
    class Json {
    public:
        explicit Json(const wchar_t* value);
        explicit Json(const std::filesystem::path& path);
        ~Json();

        bool SetValue(const std::wstring& path, const ::Json::Value& value);

        bool SetBool(const std::wstring& path, bool value) {
            return SetValue(path, value);
        }

        bool SetDouble(const std::wstring& path, double value) {
            return SetValue(path, value);
        }

        bool SetInteger(const std::wstring& path, int32_t value) {
            return SetValue(path, value);
        }

        bool SetString(const std::wstring& path, const std::wstring& value) {
            return SetValue(path, Encoding::wstring_to_utf8(value));
        }

        bool Save();

    private:
        std::filesystem::path m_path;
        ::Json::Value m_json;
    };
}

#include <fstream>

#include "json/json_utils.h"
#include "json/value.h"

#include "common/encoding.h"
#include "string/string.h"

namespace OpenWG::Utils::JSON {

    Json::Json(const std::filesystem::path &path) {
        m_path = path;
        if (std::filesystem::exists(path)) {
            std::ifstream ifs(path);
            ifs >> m_json;
        }
    }

    Json::Json(const wchar_t *value) {
        if (value) {
            auto value_u8 = Encoding::wstring_to_utf8(value);
            std::stringstream stream(value_u8);
            stream >> m_json;
        }
    }

    Json::~Json() {
        Save();
    }

    bool Json::ContainsKey(const std::wstring &path) {
        auto node = m_json;

        try {
            for (const auto &token: String::Split(Encoding::wstring_to_utf8(path), '/')) {
                node = node[token.c_str()];
            }
        }
        catch (::Json::LogicError &) {
            return false;
        }

        return !node.isNull();
    }

    std::optional<std::wstring> Json::GetString(const std::wstring &path) {
        auto node = m_json;

        try {
            for (const auto &token: String::Split(Encoding::wstring_to_utf8(path), '/')) {
                node = node[token.c_str()];
            }
        }
        catch (::Json::LogicError &) {
            return {};
        }

        if(node.isNull()) {
            return {};
        }
        return Encoding::utf8_to_wstring(node.asString());
    }

    bool Json::Save() {
        bool result{false};
        if (!m_path.empty()) {
            ::Json::StyledStreamWriter writer("  ");
            std::ofstream ofs(m_path);
            writer.write(ofs, m_json);
            result = true;
        }

        return result;
    }

    bool Json::SetValue(const std::wstring &path, const ::Json::Value &value) {
        bool result = false;

        if(path.empty() || !path.starts_with(L'/') || path.ends_with(L'/')){
            return false;
        }

        auto* node = &m_json;
        auto tokens = String::Split(path,L'/');
        for(size_t idx = 1; idx < tokens.size()- 1; idx++) {
            auto token_u8 = Encoding::wstring_to_utf8(tokens[idx]);
            if (!node->isMember(token_u8)) {
                (*node)[token_u8] = ::Json::Value(::Json::ValueType::objectValue);
            }
            node = &(*node)[token_u8];
        }

        auto name_u8 = Encoding::wstring_to_utf8(tokens.back());
        if(node->isMember(name_u8)){
            auto val_copy = value;
            (*node)[name_u8].swapPayload(val_copy);
        }
        else {
            (*node)[name_u8] = value;
        }

        result = true;
        return result;
    }

}

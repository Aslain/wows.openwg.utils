#include <fstream>

#include "common/encoding.h"
#include "json/json_utils.h"

namespace OpenWG::Utils::JSON{
    Json::Json(const std::filesystem::path& path) {
        m_path = path;
        if (std::filesystem::exists(path)) {
            std::ifstream ifs(path);
            m_json = nlohmann::json::parse(ifs);
        }
    }

    Json::~Json() {

    }

    bool Json::Save() {
        bool result{false};
        if (!m_path.empty()) {
            std::ofstream ofs(m_path);
            ofs.width(4);
            ofs << m_json;
            result = true;
        }

        return result;
    }

    bool Json::SetBool(const std::wstring &path, bool value) {
        bool result = false;

        try {
            auto pointer = nlohmann::json::json_pointer(Encoding::wstring_to_utf8(path));
            m_json[pointer] = value;
            result = true;
        } catch(nlohmann::json::exception&){

        }

        return result;
    }
}

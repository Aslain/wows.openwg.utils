#include "xml/xml_utils.h"

namespace OpenWG::Utils::XML {

    XML::XML(const std::filesystem::path &path) {
        if (std::filesystem::exists(path)) {
            m_doc.load_file(path.wstring().c_str());
        }
    }

    XML::~XML() {
    }

    bool XML::AddKey(const std::wstring &path, const std::wstring &name, const std::wstring &value) {
        bool result{false};

        auto node = m_doc.select_nodes(path.c_str());
        if (node.size() == 1) {
            auto child = node.first().node().append_child(name.c_str());
            result = child.text().set(value.c_str());
        }

        return result;
    }

    bool XML::ContainsKey(const std::wstring &path) {
        auto result = m_doc.select_nodes(path.c_str());
        return !result.empty();
    }

    bool XML::ContainsKey(const std::wstring& path, const std::wstring& value) {
        auto result = m_doc.select_nodes(path.c_str());
        if (!result.empty()) {
            for (const auto &el: result) {
                if (wcscmp(el.node().text().get(), value.c_str()) == 0) {
                    return true;
                }
            }
        }

        return false;
    }

    bool XML::Save(const std::filesystem::path &path) {
        bool result{false};
        if (!path.empty()) {
            result = m_doc.save_file(path.wstring().c_str());
        }

        return result;
    }
}

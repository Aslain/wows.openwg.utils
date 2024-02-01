// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#include <iterator>

#include "fs/fs.h"
#include "fs/fs_search.h"

namespace OpenWG::Utils::FS {

    void Search::QueryFolder(const std::wstring &regex, size_t max_depth) {
        m_depth_max = max_depth;
        m_regex = regex;
        m_results.clear();
        for (auto &drive: Filesystem::GetLogicalDrives()) {
            m_results.splice(m_results.end(), queryFolder(drive, 1));
        }
    }

    std::list<std::filesystem::path>
    Search::queryFolder(const std::filesystem::path &path, size_t depth) {
        std::list<std::filesystem::path> result;

        if (depth < m_depth_max) {
            try {
                for (const auto &item: std::filesystem::directory_iterator(path)) {
                    if (!is_directory(item)) {
                        continue;
                    }
                    result.splice(result.end(), queryFolder(item, depth + 1));
                }
            }
            catch (std::exception &) {
            }
        }

        const auto &name = path.filename().wstring();
        if (std::regex_match(name.begin(), name.end(), m_regex)) {
            result.push_back(path);
        }

        return result;
    }

    std::filesystem::path Search::GetItem(size_t index) const {
        if(index>=m_results.size()){
            return {};
        }
        return *std::next(m_results.begin(), index);
    }

    size_t Search::GetCount() const {
        return m_results.size();
    }
}

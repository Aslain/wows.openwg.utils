// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

#include "fs/fs.h"
#include "fs/fs_search.h"

namespace OpenWG::Utils::FS {

    void Search::QueryFolder(const std::wstring &regex, size_t max_depth) {
        m_depth_max = max_depth;
        m_regex = regex;
        m_results.clear();
        for(auto& drive: Filesystem::GetLogicalDrives()){
            auto results_drive = queryFolder(drive, 1);
            m_results.insert(m_results.end(), results_drive.begin(), results_drive.end());
        }
    }

    std::vector<std::filesystem::path>
    Search::queryFolder(const std::filesystem::path &path, size_t depth) {
        std::vector<std::filesystem::path> result;

        if (depth < m_depth_max) {
            try {
                for (auto &item: std::filesystem::directory_iterator(path)) {
                    if (!is_directory(item)) {
                        continue;
                    }
                    auto results_sub = queryFolder(item, depth + 1);
                    result.insert(result.end(), results_sub.begin(), results_sub.end());
                }
            }
            catch (std::exception &) {
            }
        }

        const auto &name = path.filename().wstring();
        std::wsmatch match;
        if (std::regex_match(name.begin(), name.end(), match, m_regex)) {
            result.push_back(path);
        }

        return result;
    }

    std::filesystem::path Search::GetItem(size_t index) const {
        if(index>=m_results.size()){
            return {};
        }

        return m_results[index];
    }

    size_t Search::GetCount() const {
        return m_results.size();
    }
}

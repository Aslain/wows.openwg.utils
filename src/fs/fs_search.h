// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <regex>
#include <string>
#include <vector>

namespace OpenWG::Utils::FS {
    class Search{

    public:
        void QueryFolder(const std::wstring& regex, size_t max_depth);

        [[nodiscard]] size_t GetCount() const;
        [[nodiscard]] std::filesystem::path GetItem(size_t index) const;
    private:
        std::vector<std::filesystem::path> queryFolder(const std::filesystem::path& path, size_t depth);

        std::vector<std::filesystem::path> m_results;
        std::wregex m_regex;
        size_t m_depth_max;
    };
}
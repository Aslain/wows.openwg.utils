// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

namespace OpenWG::Utils::Wine {

    struct WineStatus {
        bool running_on = false;
        wchar_t *build = nullptr;
        wchar_t *system = nullptr;
        wchar_t *release = nullptr;
    };

    [[nodiscard]] WineStatus GetStatus();
}

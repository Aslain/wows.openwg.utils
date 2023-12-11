// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

#pragma once

//
// Includes
//

// stdlib
#include <cstdint>
#include <string>



//
// Public
//

namespace OpenWG::Utils::Network {
    uint32_t Resolve(const std::wstring& host);
}

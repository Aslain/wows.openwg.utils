// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

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
    int32_t Ping(uint32_t addr, int32_t timeout);
}

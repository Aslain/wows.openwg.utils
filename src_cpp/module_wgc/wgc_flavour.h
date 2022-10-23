// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <cstdint>

enum class WgcFlavour: int32_t {
    Unknown  = 0,
    WG       = 1,
    China360 = 2,
    Steam    = 3,
    Lesta    = 4,
};
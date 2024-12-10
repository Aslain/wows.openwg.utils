// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#pragma once

//
// Includes
//

// stdlib
#include <filesystem>



//
// Namespace
//

namespace OpenWG::Utils::Image
{
    void* LoadToBitmap(const wchar_t* filename);
    void* LoadToBitmap(const std::filesystem::path& filename);
    bool FreeBitmap(void* bitmap);
}

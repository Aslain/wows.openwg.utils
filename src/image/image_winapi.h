// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#pragma once

//
// Includes
//

// stdlib
#include <filesystem>

// windows
#include <windows.h>



//
// Namespace
//

namespace OpenWG::Utils::Image
{
    // Bitmap
    bool BitmapAlphaPremultiply(HBITMAP h_bitmap);
    HBITMAP BitmapBlend(HBITMAP im1_bitmap, HBITMAP im2_bitmap);
    bool BitmapFree(HBITMAP bitmap);
    bool BitmapGetSize(HBITMAP h_bitmap, int* width, int* height);
    HBITMAP BitmapLoad(const wchar_t* filename);
    HBITMAP BitmapLoad(const std::filesystem::path& filename);

    // Brush
    HBRUSH BrushCreate(HBITMAP bitmap);
    bool BrushFree(HBRUSH brush);
}

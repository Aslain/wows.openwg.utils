// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#pragma once

#if defined(_WIN32)

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
    bool BitmapBlend(HBITMAP im1_bitmap, HBITMAP im2_bitmap, int dst_x, int dst_y);
    HBITMAP BitmapClone(HBITMAP bitmap);
    bool BitmapFree(HBITMAP bitmap);
    bool BitmapGetSize(HBITMAP h_bitmap, int* width, int* height);
    HBITMAP BitmapLoad(const wchar_t* filename);
    HBITMAP BitmapLoad(const std::filesystem::path& filename);
    HBITMAP BitmapMultiplyColor(HBITMAP bitmap, float r_scale, float g_scale, float b_scape, float a_scale);
    HBITMAP BitmapResize(HBITMAP bitmap, int width, int height);

    // Brush
    HBRUSH BrushCreate(HBITMAP bitmap);
    bool BrushFree(HBRUSH brush);
}

#endif

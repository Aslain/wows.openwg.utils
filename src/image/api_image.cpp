// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2025 OpenWG.Utils Contributors

//
// Includes
//

// OpenWG.Utils
#include "image/api_image.h"
#include "image/image_winapi.h"



//
// Implementation
//

XVMEXT_API_CALL bool IMAGE_BitmapAlphaPremultiply(void* bitmap)
{
    if (!bitmap)
    {
        return false;
    }

    return OpenWG::Utils::Image::BitmapAlphaPremultiply(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL bool IMAGE_BitmapBlend(_In_ void* bitmap_1, _In_ void* bitmap_2, int dst_x, int dst_y)
{
    if (!bitmap_1 || !bitmap_2)
    {
        return false;
    }

    return OpenWG::Utils::Image::BitmapBlend(static_cast<HBITMAP>(bitmap_1), static_cast<HBITMAP>(bitmap_2), dst_x, dst_y);
}

XVMEXT_API_CALL void* IMAGE_BitmapClone(_In_ void* bitmap)
{
    if (!bitmap)
    {
        return nullptr;
    }

    return OpenWG::Utils::Image::BitmapClone(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL bool IMAGE_BitmapFree(_In_ void* bitmap)
{
    if (!bitmap)
    {
        return false;
    }

    return OpenWG::Utils::Image::BitmapFree(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL int IMAGE_BitmapGetWidth(_In_ void* bitmap)
{
    if (!bitmap)
    {
        return 0;
    }

    int width = 0, height = 0;
    OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), &width, &height);
    return width;
}

XVMEXT_API_CALL int IMAGE_BitmapGetHeight(_In_ void* bitmap)
{
    if (!bitmap)
    {
        return false;
    }

    int width = 0, height = 0;
    OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), &width, &height);
    return height;
}

XVMEXT_API_CALL bool IMAGE_BitmapGetSize(_In_ void* bitmap, _Out_ int* width, _Out_ int* height)
{
    if (!bitmap)
    {
        return false;
    }

    return OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), width, height);
}

XVMEXT_API_CALL void* IMAGE_BitmapLoadW(_In_ const wchar_t* filename){
    if (!filename)
    {
        return nullptr;
    }

    return OpenWG::Utils::Image::BitmapLoad(filename);
}

XVMEXT_API_CALL void* IMAGE_BitmapMultiplyColor(_In_ void* bitmap, float r_scale, float g_scale, float b_scape, float a_scale)
{
    if (!bitmap)
    {
        return nullptr;
    }

    return OpenWG::Utils::Image::BitmapMultiplyColor(static_cast<HBITMAP>(bitmap), r_scale, g_scale, b_scape, a_scale);
}


void* IMAGE_BitmapResize(void* bitmap, int width, int height)
{
    if (!bitmap)
    {
        return nullptr;
    }

    return OpenWG::Utils::Image::BitmapResize(static_cast<HBITMAP>(bitmap), width, height);
}



//
// Brush
//

XVMEXT_API_CALL void* IMAGE_BrushCreate(_In_ void* bitmap)
{
    if (!bitmap)
    {
        return nullptr;
    }

    return OpenWG::Utils::Image::BrushCreate(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL bool IMAGE_BrushFree(_In_ void* brush)
{
    if (!brush)
    {
        return false;
    }

    return OpenWG::Utils::Image::BrushFree(static_cast<HBRUSH>(brush));
}

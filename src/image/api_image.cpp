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
    bool result = false;

#if defined(_WIN32)
    if (bitmap)
    {
        result = OpenWG::Utils::Image::BitmapAlphaPremultiply(static_cast<HBITMAP>(bitmap));
    }
#endif

    return result;
}

XVMEXT_API_CALL bool IMAGE_BitmapBlend(_In_ void* bitmap_1, _In_ void* bitmap_2, int dst_x, int dst_y)
{
    bool result = false;

#if defined(_WIN32)
    if (bitmap_1 && bitmap_2)
    {
        result = OpenWG::Utils::Image::BitmapBlend(static_cast<HBITMAP>(bitmap_1), static_cast<HBITMAP>(bitmap_2), dst_x, dst_y);
    }
#endif

    return result;
}

XVMEXT_API_CALL void* IMAGE_BitmapClone(_In_ void* bitmap)
{
    void* result = nullptr;

#if defined(_WIN32)
    if (bitmap)
    {
        result = OpenWG::Utils::Image::BitmapClone(static_cast<HBITMAP>(bitmap));
    }
#endif

    return result;
}

XVMEXT_API_CALL bool IMAGE_BitmapFree(_In_ void* bitmap)
{
    bool result = false;

#if defined(_WIN32)
    if (bitmap)
    {
        result = OpenWG::Utils::Image::BitmapFree(static_cast<HBITMAP>(bitmap));
    }
#endif

    return result;
}

XVMEXT_API_CALL int IMAGE_BitmapGetWidth(_In_ void* bitmap)
{
    int width = 0, height = 0;

#if defined(_WIN32)
    if (bitmap)
    {
        OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), &width, &height);
    }
#endif

    return width;
}

XVMEXT_API_CALL int IMAGE_BitmapGetHeight(_In_ void* bitmap)
{
    int width = 0, height = 0;

#if defined(_WIN32)
    if (bitmap)
    {
        OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), &width, &height);
    }
#endif

    return height;
}

XVMEXT_API_CALL bool IMAGE_BitmapGetSize(_In_ void* bitmap, _Out_ int* width, _Out_ int* height)
{
    bool result = false;

    if (bitmap && width && height)
    {
        *width = 0;
        *height = 0;
#if defined(_WIN32)
        result = OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), width, height);
#endif
    }

    return result;
}

XVMEXT_API_CALL void* IMAGE_BitmapLoadW(_In_ const wchar_t* filename){
    void* result = nullptr;

#if defined(_WIN32)
    if (filename)
    {
        result = OpenWG::Utils::Image::BitmapLoad(filename);
    }
#endif

    return result;
}

XVMEXT_API_CALL void* IMAGE_BitmapMultiplyColor(_In_ void* bitmap, float r_scale, float g_scale, float b_scape, float a_scale)
{
    void* result = nullptr;

#if defined(_WIN32)
    if (bitmap)
    {
        result = OpenWG::Utils::Image::BitmapMultiplyColor(static_cast<HBITMAP>(bitmap), r_scale, g_scale, b_scape, a_scale);
    }
#endif

    return result;
}


void* IMAGE_BitmapResize(void* bitmap, int width, int height)
{
    void* result = nullptr;

#if defined(_WIN32)
    if (bitmap)
    {
        result = OpenWG::Utils::Image::BitmapResize(static_cast<HBITMAP>(bitmap), width, height);
    }
#endif

    return result;
}



//
// Brush
//

XVMEXT_API_CALL void* IMAGE_BrushCreate(_In_ void* bitmap)
{
    void* result = nullptr;

#if defined(_WIN32)
    if (bitmap)
    {
        result = OpenWG::Utils::Image::BrushCreate(static_cast<HBITMAP>(bitmap));
    }
#endif

    return result;
}

XVMEXT_API_CALL bool IMAGE_BrushFree(_In_ void* brush)
{
    bool result = false;

#if defined(_WIN32)
    if (brush)
    {
        result = OpenWG::Utils::Image::BrushFree(static_cast<HBRUSH>(brush));
    }
#endif

    return result;
}

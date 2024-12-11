// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2024 OpenWG.Utils Contributors

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
    return OpenWG::Utils::Image::BitmapAlphaPremultiply(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL void* IMAGE_BitmapBlend(_In_ void* bitmap_1, _In_ void* bitmap_2)
{
    return OpenWG::Utils::Image::BitmapBlend(static_cast<HBITMAP>(bitmap_1), static_cast<HBITMAP>(bitmap_2));
}

XVMEXT_API_CALL bool IMAGE_BitmapFree(_In_ void* bitmap)
{
    return OpenWG::Utils::Image::BitmapFree(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL int IMAGE_BitmapGetWidth(_In_ void* bitmap)
{
    int width = 0, height = 0;
    OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), &width, &height);
    return width;
}

XVMEXT_API_CALL int IMAGE_BitmapGetHeight(_In_ void* bitmap)
{
    int width = 0, height = 0;
    OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), &width, &height);
    return height;
}

XVMEXT_API_CALL bool IMAGE_BitmapGetSize(_In_ void* bitmap, _Out_ int* width, _Out_ int* height)
{
    return OpenWG::Utils::Image::BitmapGetSize(static_cast<HBITMAP>(bitmap), width, height);
}

XVMEXT_API_CALL void* IMAGE_BitmapLoadW(_In_ const wchar_t* filename){
    return OpenWG::Utils::Image::BitmapLoad(filename);
}

void* IMAGE_BitmapResize(void* bitmap, int width, int height)
{
    return OpenWG::Utils::Image::BitmapResize(static_cast<HBITMAP>(bitmap), width, height);
}



//
// Brush
//

XVMEXT_API_CALL void* IMAGE_BrushCreate(_In_ void* bitmap)
{
    return OpenWG::Utils::Image::BrushCreate(static_cast<HBITMAP>(bitmap));
}

XVMEXT_API_CALL bool IMAGE_BrushFree(_In_ void* brush)
{
    return OpenWG::Utils::Image::BrushFree(static_cast<HBRUSH>(brush));
}

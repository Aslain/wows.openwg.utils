// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2024 OpenWG.Utils Contributors

//
// Includes
//

// OpenWG.Utils
#include "image/api_image.h"
#include "image/image_convert.h"
#include "image/image_winapi.h"



//
// Implementation
//

XVMEXT_API_CALL void IMAGEDRAW_PngToBmp(const wchar_t* filename)
{
    OpenWG::Utils::Image::PngToBmp(filename);
}

XVMEXT_API_CALL void* IMAGE_LoadW(_In_ const wchar_t* filename){
    return OpenWG::Utils::Image::LoadToBitmap(filename);
}

XVMEXT_API_CALL bool IMAGE_FreeBitmapW(_In_ void* bitmap)
{
    return OpenWG::Utils::Image::FreeBitmap(bitmap);
}
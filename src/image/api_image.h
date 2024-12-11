// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2024 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Includes
//

// OpenWG.Utils
#include "common/api_common.h"



//
// Bitmap
//

XVMEXT_API_CALL bool IMAGE_BitmapAlphaPremultiply(_In_ void* bitmap);

XVMEXT_API_CALL void* IMAGE_BitmapBlend(_In_ void* bitmap_1, _In_ void* bitmap_2);

XVMEXT_API_CALL bool IMAGE_BitmapFree(_In_ void* bitmap);

XVMEXT_API_CALL int IMAGE_BitmapGetHeight(_In_ void* bitmap);

XVMEXT_API_CALL int IMAGE_BitmapGetWidth(_In_ void* bitmap);

XVMEXT_API_CALL void* IMAGE_BitmapLoadW(_In_ const wchar_t* filename);



//
// Brush
//

XVMEXT_API_CALL void* IMAGE_BrushCreate(_In_ void* bitmap);

XVMEXT_API_CALL bool IMAGE_BrushFree(_In_ void* brush);

#ifdef __cplusplus
}
#endif

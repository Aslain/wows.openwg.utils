// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2025 OpenWG.Utils Contributors

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

XVMEXT_API_CALL bool IMAGE_BitmapBlend(_In_ void* bitmap_dst, _In_ void* bitmap_alpha, int dst_x, int dst_y);

XVMEXT_API_CALL void* IMAGE_BitmapClone(_In_ void* bitmap);

XVMEXT_API_CALL bool IMAGE_BitmapFree(_In_ void* bitmap);

XVMEXT_API_CALL int IMAGE_BitmapGetHeight(_In_ void* bitmap);

XVMEXT_API_CALL int IMAGE_BitmapGetWidth(_In_ void* bitmap);

XVMEXT_API_CALL void* IMAGE_BitmapLoadW(_In_ const wchar_t* filename);

XVMEXT_API_CALL void* IMAGE_BitmapMultiplyColor(_In_ void* bitmap, float r_scale, float g_scale, float b_scape, float a_scale);

XVMEXT_API_CALL void* IMAGE_BitmapResize(_In_ void* bitmap, int width, int height);


//
// Brush
//

XVMEXT_API_CALL void* IMAGE_BrushCreate(_In_ void* bitmap);

XVMEXT_API_CALL bool IMAGE_BrushFree(_In_ void* brush);

#ifdef __cplusplus
}
#endif

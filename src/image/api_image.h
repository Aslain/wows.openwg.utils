// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL void IMAGEDRAW_PngToBmp(_In_ const wchar_t* filename);

XVMEXT_API_CALL void* IMAGE_LoadBitmapW(_In_ const wchar_t* filename);

XVMEXT_API_CALL bool IMAGE_FreeBitmapW(_In_ void* bitmap);

#ifdef __cplusplus
}
#endif

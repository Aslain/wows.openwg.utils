// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL int32_t __cdecl SPLASHSCREEN_ShowSplashScreenW(_In_ const wchar_t *file_path, int32_t seconds);

#ifdef __cplusplus
}
#endif

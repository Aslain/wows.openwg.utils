// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Includes
//

#include "common/api_common.h"



//
// Functions
//

XVMEXT_API_CALL bool FS_File_IsEqualW(const wchar_t* path_1, const wchar_t* path_2);

#ifdef __cplusplus
}
#endif

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

XVMEXT_API_CALL bool FS_FileEqualW(const wchar_t* path_1, const wchar_t* path_2);


XVMEXT_API_CALL bool FS_FileExistsW(const wchar_t* path);


#ifdef __cplusplus
}
#endif

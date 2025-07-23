// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Includes
//

// stdlib
#include <stdint.h>

//openwg.utils
#include "common/api_common.h"



//
// Functions
//

// File
XVMEXT_API_CALL bool FS_FileEqualW(const wchar_t* path_1, const wchar_t* path_2);
XVMEXT_API_CALL uint32_t FS_FileSizeW(const wchar_t* path_1);
XVMEXT_API_CALL bool FS_FileExistsW(const wchar_t* path);

// Sarch
XVMEXT_API_CALL void* FS_Search_QueryFolderW(const wchar_t* path, uint32_t max_depth);
XVMEXT_API_CALL bool FS_Search_Close(void* object);
XVMEXT_API_CALL uint32_t FS_Search_GetCount(void* object);
XVMEXT_API_CALL uint32_t FS_Search_GetPathW(void* object, uint32_t index, wchar_t* buf, uint32_t buf_len);


#ifdef __cplusplus
}
#endif

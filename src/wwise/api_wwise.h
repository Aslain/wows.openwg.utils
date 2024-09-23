// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Includes
//

#include "common/api_common.h"



//
// Enums
//

enum WwiseLicense {
    WwiseLicense_Unknown    = 0,
    WwiseLicense_Unlicensed = 1,
    WwiseLicense_Wargaming  = 2,
};



//
// Functions
//

XVMEXT_API_CALL void* WWISE_OpenFileW(const wchar_t *path);

XVMEXT_API_CALL bool WWISE_Close(void* object);

XVMEXT_API_CALL int32_t WWISE_LicenseGet(void* object);

XVMEXT_API_CALL int32_t WWISE_VersionGet(void* object);

XVMEXT_API_CALL bool WWISE_LicenseSet(void* object, int32_t license);

XVMEXT_API_CALL bool WWISE_BKHD_ProjectId_Set(void* object, uint32_t project_id);

XVMEXT_API_CALL bool WWISE_SaveFileW(void* object, const wchar_t* path);


#ifdef __cplusplus
}
#endif

// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL int32_t PROCESS_GetRunningInDirectoryW(_In_ const wchar_t* directory_path, _Out_ wchar_t* output_list, int32_t output_list_size);

XVMEXT_API_CALL int32_t PROCESS_TerminateProcess(_In_ const wchar_t* process_path);

#ifdef __cplusplus
}
#endif

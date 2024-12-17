// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL bool INNO_ComponentEntryGetNameW(_In_ void* obj, _In_ wchar_t* buf, _In_ int32_t buf_len);

XVMEXT_API_CALL bool INNO_ComponentEntryGetDescriptionW(_In_ void* obj, _In_ wchar_t* buf, _In_ int32_t buf_len);

XVMEXT_API_CALL bool INNO_ComponentEntryCompareNameW(_In_ const wchar_t* name_1, _In_ const wchar_t* name_2);


#ifdef __cplusplus
}
#endif

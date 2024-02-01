// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL int32_t NETWORK_PingW(_In_ const wchar_t* hostname, _In_ int32_t timeout);
XVMEXT_API_CALL uint32_t NETWORK_ResolveW(_In_ const wchar_t* hostname);


#ifdef __cplusplus
}
#endif

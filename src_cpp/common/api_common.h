// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_OPENWGUTILS
    #define XVMEXT_API_CALL __declspec(dllexport)
#else
    #define XVMEXT_API_CALL __declspec(dllimport)
#endif

#ifdef __cplusplus
}
#endif
// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef BUILD_OPENWGUTILS
#define XVMEXT_API_CALL extern "C" __declspec(dllexport)
#else
#define XVMEXT_API_CALL extern "C" __declspec(dllimport)
#endif

#ifndef _In_
#define _In_
#endif

#ifndef _Out_
#define _Out_
#endif

#ifdef __cplusplus
}
#endif
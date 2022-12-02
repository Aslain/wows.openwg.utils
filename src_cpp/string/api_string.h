// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

/**
 * Replace pattern in a string using regexpr
 * @param input input string
 * @param pattern_search search pattern
 * @param pattern_replace replace pattern
 * @param output output buffer
 * @param output_len output length in wchar_t units
 * @return
 *   * 1   -- success
 *   * 0   -- invalid pointer
 *   * -X  -- output buffer is too small, X wchar_t units are required
 */
XVMEXT_API_CALL int32_t STRING_ReplaceRegex(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search, _In_ const wchar_t* pattern_replace, _Out_ wchar_t* output, _In_ int32_t output_len);

#ifdef __cplusplus
}
#endif

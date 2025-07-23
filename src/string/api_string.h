// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2025 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "common/api_common.h"

/**
 * Match pattern in a string using regexpr
 * @param input input string
 * @param pattern_search search pattern
 * @return
 *   * 1   -- martch
 *   * 0   -- error or no matchinvalid pointer
 *   * -X  -- output buffer is too small, X wchar_t units are required
 */
XVMEXT_API_CALL bool STRING_MatchRegex(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search);


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

/**
 * Replace pattern in a string using regexpr
 * @param input input string
 * @param pattern_search search pattern
 * @param pattern_replace replace pattern
 * @param output output buffer
 * @param output_len output length in wchar_t units
 * @param first_only replace only the first occurrence
 * @return
 *   * 1   -- success
 *   * 0   -- invalid pointer
 *   * -X  -- output buffer is too small, X wchar_t units are required
 */
XVMEXT_API_CALL int32_t STRING_ReplaceRegexEx(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search, _In_ const wchar_t* pattern_replace, _Out_ wchar_t* output, _In_ int32_t output_len, _In_ bool first_only);

#ifdef __cplusplus
}
#endif

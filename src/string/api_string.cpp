//
// Includes
//

// windows
#include <windows.h>

#include "string/api_string.h"
#include "string/string.h"

using namespace OpenWG::Utils;

//
// Functions
//

XVMEXT_API_CALL bool STRING_MatchRegex(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search) {
    // check ptrs
    if (!input || !pattern_search) {
        return false;
    }

    try {
        return String::MatchRegex(input, pattern_search);
    }
    catch (std::exception &e) {
        OutputDebugStringA(e.what());
        return false;
    }
}


int32_t STRING_ReplaceRegex(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search, _In_ const wchar_t* pattern_replace, _Out_ wchar_t* output, _In_ int32_t output_len) {
    return STRING_ReplaceRegexEx(input, pattern_search, pattern_replace, output, output_len, false);
}

int32_t STRING_ReplaceRegexEx(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search, _In_ const wchar_t* pattern_replace, _Out_ wchar_t* output, _In_ int32_t output_len, _In_ bool first_only) {
    // check ptrs
    if (!input || !pattern_search || !pattern_replace || !output) {
        return 0;
    }

    // clear input string
    output[0] = L'\0';

    std::wstring result_w{};
    try {
        result_w = String::ReplaceRegex(input, pattern_search, pattern_replace, first_only);
        if (output_len > result_w.size()) {
            wcscpy_s(output, output_len, result_w.c_str());
            return 1;
        }
    }
    catch (std::exception& e) {
        OutputDebugStringA(e.what());
        return 0;
    }

    return -static_cast<int>(result_w.size());
}


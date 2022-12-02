//
// Includes
//

#include "string/api_string.h"
#include "string/string.h"

using namespace OpenWG::Utils;

//
// Functions
//

int32_t STRING_ReplaceRegex(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search, _In_ const wchar_t* pattern_replace, _Out_ wchar_t* output, _In_ int32_t output_len) {
    // check ptrs
    if (!input || !pattern_search || !pattern_replace || !output) {
        return 0;
    }

    // clear input string
    output[0] = L'\0';

    auto result_w = String::ReplaceRegex(input, pattern_search, pattern_replace);
    if (output_len > result_w.size()) {
        wcscpy_s(output, output_len, result_w.c_str());
        return 1;
    }

    return -static_cast<int>(result_w.size());
}


//
// Includes
//

// stdlib
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

// windows
#if defined(_WIN32)
#include <windows.h>
#endif

// openwg.utils
#include "string/api_string.h"
#include "string/string.h"
#include "common/encoding.h"

using namespace OpenWG::Utils;

//
// Linux
//

#if !defined(_WIN32)
#define wcscpy_s(a,b,c) wcscpy(a,c)
#endif



//
// Functions
//

int32_t STRING_LoadFromFile(_In_ const wchar_t* filepath, _Out_ wchar_t* output, _In_ int32_t output_len)
{
    if (!filepath || !output || output_len <= 0)
    {
        return -1;
    }

    output[0] = L'\0';

    std::ifstream file(std::filesystem::path(filepath), std::ios::binary);
    if (!file.is_open())
    {
        return -1;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size == 0)
    {
        return 0;
    }

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size))
    {
        return -1;
    }

    char* p_buffer = buffer.data();
    auto buffer_len = static_cast<int32_t>(buffer.size());

    // BOMs
    const unsigned char bom_utf8[] = { 0xEF, 0xBB, 0xBF };
    const unsigned char bom_utf16_le[] = { 0xFF, 0xFE };

    bool is_utf16 = false;

    if (buffer_len >= 2 && memcmp(p_buffer, bom_utf16_le, 2) == 0)
    {
        is_utf16 = true;
        p_buffer += 2;
        buffer_len -= 2;
    }
    else if (buffer_len >= 3 && memcmp(p_buffer, bom_utf8, 3) == 0)
    {
        p_buffer += 3;
        buffer_len -= 3;
    }
    
    std::wstring result_w;
    if (is_utf16)
    {
        result_w.assign(reinterpret_cast<wchar_t*>(p_buffer), buffer_len / sizeof(wchar_t));
    }
    else
    {
        // Don't include null terminator in the string for conversion
        result_w = Encoding::utf8_to_wstring(std::string(p_buffer, buffer_len));
    }

    // The +1 is for the null terminator
    if (result_w.size() + 1 < static_cast<size_t>(output_len))
    {
        wcscpy_s(output, output_len, result_w.c_str());
        return static_cast<int32_t>(result_w.size());
    }
    
    return -1;
}

XVMEXT_API_CALL bool STRING_MatchRegex(_In_ const wchar_t* input, _In_ const wchar_t* pattern_search) {
    // check ptrs
    if (!input || !pattern_search) {
        return false;
    }

    try {
        return String::MatchRegex(input, pattern_search);
    }
    catch (std::exception &e) {
#if defined(_WIN32)
        OutputDebugStringA(e.what());
#endif
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
#if defined(_WIN32)
        OutputDebugStringA(e.what());
#endif
        return 0;
    }

    return -static_cast<int>(result_w.size());
}


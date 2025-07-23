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
#include "fs/api_fs.h"

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

//
// Performs an in-place conversion of a null-terminated UTF-8 string to UTF-16LE.
// The conversion is done from the end of the buffer towards the beginning to avoid overwriting source characters.
//
// @param buffer A pointer to the buffer containing the null-terminated UTF-8 string.
//               The buffer must be large enough to hold the resulting UTF-16LE string.
//               A safe buffer size is at least (strlen(utf8_string) * 2) + 2 bytes.
// @return The length of the resulting UTF-16LE string in bytes (excluding the null terminator) on success.
//         Returns -1 if an invalid UTF-8 sequence is encountered.
//
int utf8_to_utf16le_in_place(char* buffer) {
    if (!buffer) {
        return -1;
    }

    // 1. Find the end of the null-terminated UTF-8 string.
    const char* utf8_end = buffer;
    while (*utf8_end) {
        utf8_end++;
    }
    const char* utf8_start = buffer;

    // 2. Setup write pointer at a safe position at the end of the buffer.
    // The buffer must be large enough. A capacity of at least (utf8_len * 2) + 2 is required.
    const ptrdiff_t utf8_len = utf8_end - utf8_start;
    char* write_ptr_end = buffer + utf8_len * 2 + 2;
    unsigned short* utf16_write = (unsigned short*)(write_ptr_end);

    // Write a temporary null terminator. It will be moved to the correct final position later.
    *(--utf16_write) = 0;

    // 3. Process the string from end to start.
    const unsigned char* read_ptr = (const unsigned char*)utf8_end;

    while (read_ptr > (const unsigned char*)utf8_start) {
        // 3a. Find the start of the current UTF-8 sequence by scanning backwards.
        const unsigned char* seq_end = read_ptr;
        const unsigned char* seq_start = read_ptr - 1;
        while (seq_start >= (const unsigned char*)utf8_start && (*seq_start & 0xC0) == 0x80) {
            seq_start--;
        }

        // Safety check: a UTF-8 sequence must not be longer than 4 bytes.
        if (seq_end - seq_start > 4) {
            return -1;
        }

        // 3b. Decode the sequence that starts at `seq_start`.
        const unsigned char* p = seq_start;
        unsigned char byte1 = *p++;
        unsigned int code_point = 0;

        if (byte1 < 0x80) {
            // 1-byte sequence (ASCII).
            if (seq_end - seq_start != 1) return -1; // Must be a standalone byte.
            code_point = byte1;
        } else if ((byte1 & 0xE0) == 0xC0) {
            // 2-byte sequence: 110xxxxx 10xxxxxx
            if (seq_end - seq_start != 2) return -1;
            unsigned char byte2 = *p++;
            if ((byte2 & 0xC0) != 0x80) return -1; // Invalid continuation byte.
            if (byte1 < 0xC2) return -1; // Overlong encoding (C0, C1).
            code_point = ((byte1 & 0x1F) << 6) | (byte2 & 0x3F);
        } else if ((byte1 & 0xF0) == 0xE0) {
            // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
            if (seq_end - seq_start != 3) return -1;
            unsigned char byte2 = *p++;
            unsigned char byte3 = *p++;
            if ((byte2 & 0xC0) != 0x80 || (byte3 & 0xC0) != 0x80) return -1;
            if (byte1 == 0xE0 && byte2 < 0xA0) return -1; // Overlong encoding.
            if (byte1 == 0xED && byte2 >= 0xA0) return -1; // Surrogates (U+D800..U+DFFF) are invalid in UTF-8.
            code_point = ((byte1 & 0x0F) << 12) | ((byte2 & 0x3F) << 6) | (byte3 & 0x3F);
        } else if ((byte1 & 0xF8) == 0xF0) {
            // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            if (seq_end - seq_start != 4) return -1;
            unsigned char byte2 = *p++;
            unsigned char byte3 = *p++;
            unsigned char byte4 = *p++;
            if ((byte2 & 0xC0) != 0x80 || (byte3 & 0xC0) != 0x80 || (byte4 & 0xC0) != 0x80) return -1;
            if (byte1 > 0xF4 || (byte1 == 0xF4 && byte2 >= 0x90)) return -1; // Code point > U+10FFFF.
            if (byte1 == 0xF0 && byte2 < 0x90) return -1; // Overlong encoding.
            code_point = ((byte1 & 0x07) << 18) | ((byte2 & 0x3F) << 12) | ((byte3 & 0x3F) << 6) | (byte4 & 0x3F);
        } else {
            return -1; // Invalid UTF-8 start byte.
        }

        read_ptr = seq_start; // Move read pointer for the next iteration.

        // 3c. Encode the code point into UTF-16LE and write it to the buffer.
        if (code_point < 0x10000) {
            // Fits in a single 16-bit word.
            *(--utf16_write) = (unsigned short)code_point;
        } else {
            // Requires a surrogate pair for code points U+10000 and above.
            code_point -= 0x10000;
            *(--utf16_write) = (unsigned short)(0xDC00 | (code_point & 0x03FF)); // Low surrogate
            *(--utf16_write) = (unsigned short)(0xD800 | (code_point >> 10));   // High surrogate
        }
    }

    // 4. Move the converted string from the end of the buffer to the beginning.
    char* result_start = (char*)utf16_write;
    const int new_len_bytes = (char*)write_ptr_end - result_start - 2; // -2 for the temp null terminator

    if (result_start != buffer) {
        memmove(buffer, result_start, new_len_bytes);
    }
    
    // 5. Place the final null terminator at the end of the newly converted string.
    buffer[new_len_bytes] = '\0';
    buffer[new_len_bytes + 1] = '\0';

    return new_len_bytes;
}

int32_t STRING_LoadFromFile(_In_ const wchar_t* filepath, _Out_ wchar_t* output, _In_ uint32_t output_len) {
    // invalid args
    if (!filepath || !output || !output_len)
    {
        return INT_MIN;
    }
    output[0] = L'\0';

    // file does not exists
    if (!FS_FileExistsW(filepath)) {
        return INT_MIN;
    }

    // get file size
    int32_t filesize = FS_FileSizeW(filepath);

    // we require x2 size of file in case we are performing utf8->utf16 conversion
    if (output_len < filesize*2) {
        return -filesize*2;
    }

    // exit early in case of zero byte
    if (!filesize) {
        return 0;
    }

    // allocate buf
    std::vector<char> buffer(filesize);

    // read file
    {
        std::ifstream file(std::filesystem::path(filepath), std::ios::binary);
        if (!file.is_open()) {
            return INT_MIN;
        }
        if (!file.read(reinterpret_cast<char*>(output), filesize)) {
            return INT_MIN;
        }
    }

    // conversion

    // case 1: utf16 -- do nothing
    {
        const unsigned char bom_utf16_le[] = { 0xFF, 0xFE };
        if (output_len >= 2 && memcmp(output, bom_utf16_le, sizeof(bom_utf16_le)) == 0) {
            return filesize;
        }
    }

    // case 2: utf8-bom -- remove bom
    {
        const unsigned char bom_utf8[] = { 0xEF, 0xBB, 0xBF };
        if (output_len >= 3 && memcmp(output, bom_utf8, 3) == 0) {
            filesize -= 3;
            char* reinter = reinterpret_cast<char*>(output);
            memmove(&reinter[0], &reinter[3], filesize);
        }
    }

    // case 3: utf8 -> utf16 conversion
    {
    	// The buffer (`output`) now contains the UTF-8 string (without BOM).
    	// We will treat it as a byte buffer for the conversion.
    	// First, ensure it's null-terminated for the conversion function.
    	// `filesize` is the length of the UTF-8 string in bytes.
    	char* char_buffer = reinterpret_cast<char*>(output);
    	char_buffer[filesize] = '\0';
   
    	// Perform the in-place conversion.
    	// The function `utf8_to_utf16le_in_place` expects the buffer to have enough capacity.
    	// The check `output_len < filesize * 2` at the beginning of this function helps ensure this.
    	int32_t new_len_bytes = utf8_to_utf16le_in_place(char_buffer);
   
    	if (new_len_bytes < 0) {
    		// An error occurred during conversion (invalid UTF-8 sequence).
    		output[0] = L'\0'; // Ensure output is a valid empty string on error
    		return INT_MIN;
    	}
   
    	// Return the new length of the string in bytes.
    	return new_len_bytes;
    }

    return INT_MIN;
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


// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "encoding.h"

#include <codecvt>
#include <locale>

std::wstring Encoding::utf8_to_wstring(const std::string& str)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

std::string Encoding::wstring_to_utf8(const std::wstring& str)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}

std::wstring Encoding::vec_to_base64w(const std::vector<uint8_t>& vec)
{
    static constexpr wchar_t sEncodingTable[] = {
        'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H',
        'I', L'J', L'K', L'L', L'M', L'N', L'O', L'P',
        'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X',
        'Y', L'Z', L'a', L'b', L'c', L'd', L'e', L'f',
        'g', L'h', L'i', L'j', L'k', L'l', L'm', L'n',
        'o', L'p', L'q', L'r', L's', L't', L'u', L'v',
        'w', L'x', L'y', L'z', L'0', L'1', L'2', L'3',
        '4', L'5', L'6', L'7', L'8', L'9', L'+', L'/'
    };

    size_t in_len = vec.size();
    size_t out_len = 4 * ((in_len + 2) / 3);
    std::wstring ret(out_len, L'\0');
    size_t i;
    wchar_t* p = const_cast<wchar_t*>(ret.c_str());

    for (i = 0; i < in_len - 2; i += 3) {
        *p++ = sEncodingTable[(vec[i] >> 2) & 0x3F];
        *p++ = sEncodingTable[((vec[i] & 0x3) << 4) | ((int)(vec[i + 1] & 0xF0) >> 4)];
        *p++ = sEncodingTable[((vec[i + 1] & 0xF) << 2) | ((int)(vec[i + 2] & 0xC0) >> 6)];
        *p++ = sEncodingTable[vec[i + 2] & 0x3F];
    }

    if (i < in_len) {
        *p++ = sEncodingTable[(vec[i] >> 2) & 0x3F];

        if (i == (in_len - 1)) {
            *p++ = sEncodingTable[((vec[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else {
            *p++ = sEncodingTable[((vec[i] & 0x3) << 4) | ((int)(vec[i + 1] & 0xF0) >> 4)];
            *p++ = sEncodingTable[((vec[i + 1] & 0xF) << 2)];
        }

        *p++ = '=';
    }

    return ret;
}

#pragma once

#include <string>

class Encoding
{
public:
    // convert UTF-8 string to wstring
    static std::wstring utf8_to_wstring(const std::string& str);

    // convert wstring to UTF-8 string
    static std::string wstring_to_utf8(const std::wstring& str);
};
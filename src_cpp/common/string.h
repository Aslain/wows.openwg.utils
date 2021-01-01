/* Copyright (c) 2017-2021, Mikhail Paulyshka.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <string>
#include <vector>

class String {
public:
    static std::string Trim(const std::string& str);
    static std::string LTrim(const std::string& str);
    static std::string RTrim(const std::string& str);

    static std::wstring Trim(const std::wstring& str);
    static std::wstring LTrim(const std::wstring& str);
    static std::wstring RTrim(const std::wstring& str);

    static std::vector<std::string> Split(const std::string& s, const char delim);
    static std::vector<std::wstring> Split(const std::wstring& s, const wchar_t delim);

    static std::wstring Replace(const std::wstring& where, const std::wstring& from, const std::wstring& to);

    static std::wstring Substring(const std::wstring& where, size_t from, size_t to = std::wstring::npos);


    static std::wstring VecToWstring(const std::vector<uint8_t>& vec);

};;

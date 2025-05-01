// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <algorithm>
#include <iterator>
#include <locale>
#include <regex>
#include <string>
#include <sstream>

#include "string/string.h"


namespace OpenWG::Utils {
    namespace String {

        std::string Trim(const std::string &str) {
            return LTrim(RTrim(str));
        }

        std::string LTrim(const std::string &str) {
            std::string result = str;

            auto it2 = std::find_if(result.begin(), result.end(),
                                    [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
            result.erase(result.begin(), it2);
            return result;
        }

        std::string RTrim(const std::string &str) {
            std::string result = str;

            auto it1 = std::find_if(result.rbegin(), result.rend(),
                                    [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
            result.erase(it1.base(), result.end());
            return result;
        }

        std::wstring Trim(const std::wstring &str) {
            return LTrim(RTrim(str));
        }

        std::wstring LTrim(const std::wstring &str) {
            std::wstring result = str;

            auto it2 = std::find_if(result.begin(), result.end(),
                                    [](wchar_t ch) { return !std::isspace<wchar_t>(ch, std::locale::classic()); });
            result.erase(result.begin(), it2);
            return result;
        }

        std::wstring RTrim(const std::wstring &str) {
            std::wstring result = str;

            auto it1 = std::find_if(result.rbegin(), result.rend(),
                                    [](wchar_t ch) { return !std::isspace<wchar_t>(ch, std::locale::classic()); });
            result.erase(it1.base(), result.end());
            return result;
        }

        std::vector<std::string> Split(const std::string &s, const char delim) {
            std::vector<std::string> elems;
            std::stringstream ss(s);
            std::string item;

            while (std::getline(ss, item, delim)) {
                *(std::back_inserter(elems)++) = item;
            }

            return elems;
        }

        std::vector<std::wstring> Split(const std::wstring &s, wchar_t delim) {
            std::vector<std::wstring> elems;
            std::wstringstream ss(s);
            std::wstring item;

            while (std::getline(ss, item, delim)) {
                *(std::back_inserter(elems)++) = item;
            }

            return elems;
        }

        std::vector<std::wstring> Split(const std::wstring &s, wchar_t delim, size_t limit) {
            std::vector<std::wstring> elems;
            std::wstringstream ss(s);
            std::wstring item;

            size_t idx = 1;
            while (idx < limit && std::getline(ss, item, delim)) {
                *(std::back_inserter(elems)++) = item;
                idx++;
            }

            if (std::getline(ss, item)) {
                *(std::back_inserter(elems)++) = item;
            }

            return elems;
        }

        bool MatchRegex(const std::wstring& where, const std::wstring& from) {
            std::wregex regex(from);
            return std::regex_search(where, regex);
        }

        std::wstring Replace(const std::wstring &where, const std::wstring &from, const std::wstring &to) {
            if (where.empty() || from.empty()) {
                return {where};
            }

            std::wstring result = where;

            size_t index = 0;
            while (true) {
                index = result.find(from, index);
                if (index == std::wstring::npos) {
                    break;
                }

                result.replace(index, from.size(), to);

                index += from.size();
            }

            return result;
        }

        size_t ReplaceChar(wchar_t* str, wchar_t from, wchar_t to)
        {
            size_t result = 0;
            if (str != nullptr && from != L'\0' && to != L'\0')
            {
                for (wchar_t* c = str; *c != L'\0'; c++)
                {
                    if (*c == from)
                    {
                        *c = to;
                        result++;
                    }
                }
            }
            return result;
        }

        std::wstring ReplaceRegex(const std::wstring &where, const std::wstring &from, const std::wstring &to) {
            std::wregex regex(from);
            return std::regex_replace(where, regex, to);
        }

        std::wstring Substring(const std::wstring &where, size_t from, size_t to) {
            if (from == to) {
                return {};
            }
            if (from == std::wstring::npos || from >= where.size()) {
                return {};
            }
            if (where.empty()) {
                return {};
            }

            return where.substr(from, to);
        }

        std::wstring VecToWstring(const std::vector<uint8_t> &vec) {
            std::wstring result;

            switch (vec.size()) {

                case 1: {
                    int8_t val = 0;
                    memcpy(&val, vec.data(), vec.size());
                    result = std::to_wstring(val);
                    break;
                }
                case 2: {
                    int16_t val = 0;
                    memcpy(&val, vec.data(), vec.size());
                    result = std::to_wstring(val);
                    break;
                }
                case 3:
                case 4: {
                    int32_t val = 0;
                    memcpy(&val, vec.data(), vec.size());
                    result = std::to_wstring(val);
                    break;
                }
                case 5:
                case 6:
                case 7:
                case 8: {
                    int64_t val = 0;
                    memcpy(&val, vec.data(), vec.size());
                    result = std::to_wstring(val);
                    break;
                }
                case 0:
                default: {
                    result = std::to_wstring(0);
                    break;
                }

            }

            return result;
        }

        std::wstring ToLower(const std::wstring &str) {
            auto result{str};
            transform(result.begin(), result.end(), result.begin(), ::towlower);
            return result;
        }


    }
}

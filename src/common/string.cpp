// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

#include "string.h"

namespace OpenWG::Utils::Common
{
    namespace String
    {
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
    }
}

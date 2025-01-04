// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <cstring>

// OpenWG.Utils
#include "string/string.h"
#include "inno/api_inno.h"

#include <cstdlib>


//
// Typedefs
//

// https://github.com/jrsoftware/issrc/blob/main/Projects/Src/Shared.Struct.pas#L183
struct SetupComponentEntry {
    wchar_t* name;
    wchar_t* description;
    //other fields are not interesting for us
};



//
// Functions
//

XVMEXT_API_CALL bool INNO_ComponentEntryGetNameW(void* obj, wchar_t* buf, int32_t buf_len)
{
    if (!obj || !buf || buf_len <= 0)
    {
        return false;
    }

    wcscpy_s(buf, buf_len, static_cast<SetupComponentEntry*>(obj)->name);
    OpenWG::Utils::String::ReplaceChar(buf, L'\\', L'/');
    return true;
}

XVMEXT_API_CALL bool INNO_ComponentEntryGetDescriptionW(void* obj, wchar_t* buf, int32_t buf_len)
{
    if (!obj || !buf || buf_len <= 0)
    {
        return false;
    }

    wcscpy_s(buf, buf_len, static_cast<SetupComponentEntry*>(obj)->description);
    return true;
}


XVMEXT_API_CALL bool INNO_ComponentEntryCompareNameW(const wchar_t* name_1, const wchar_t* name_2)
{
    if (!name_1 || !name_2)
    {
        return false;
    }

    wchar_t* name_1_copy = _wcsdup(name_1);
    wchar_t* name_2_copy = _wcsdup(name_2);

    OpenWG::Utils::String::ReplaceChar(name_1_copy, L'\\', L'/');
    OpenWG::Utils::String::ReplaceChar(name_2_copy, L'\\', L'/');

    bool result = wcscmp(name_1_copy, name_2_copy) == 0;

    free(name_1_copy);
    free(name_2_copy);

    return result;
}

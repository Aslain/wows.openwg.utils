// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <cstring>

// OpenWG.Utils
#include "inno/api_inno.h"



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

// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "api_bwxml.h"
#include "bwxml.h"

XVMEXT_API_CALL int32_t BWXML_UnpackW(const wchar_t* xml_in, const wchar_t* xml_out)
{
    if (xml_in == nullptr) {
        return -1;
    }

    if (xml_out == nullptr) {
        return -2;
    }

    BwXml bwxml;
    if (!bwxml.Read(xml_in)) {
        return -3;
    }

    if (!bwxml.SaveXml(xml_out)) {
        return -4;
    }

    return 0;
}

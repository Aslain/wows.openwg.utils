// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <filesystem>

// OpenWG
#include "xml/api_xml.h"
#include "xml/xml_utils.h"

using namespace OpenWG::Utils;



//
// Public
//

bool XML_AddKeyW(void *object, const wchar_t *path, const wchar_t *name, const wchar_t* value) {
    bool result = false;

    if (object && path && name && value) {
        auto *obj = reinterpret_cast<XML::XML *>(object);
        result = obj->AddKey(path, name, value);
    }

    return result;
}


bool XML_Close(void *object) {
    bool result = false;

    if (object) {
        auto *obj = reinterpret_cast<XML::XML *>(object);
        delete obj;
        result = true;
    }

    return result;
}


bool XML_ContainsKeyW(void *object, const wchar_t *path) {
    bool result = false;

    if (object && path) {
        auto *obj = reinterpret_cast<XML::XML *>(object);
        result = obj->ContainsKey(path);
    }

    return result;
}


bool XML_ContainsKeyExW(void *object, const wchar_t *path, const wchar_t* value){
    bool result = false;

    if (object && path && value) {
        auto *obj = reinterpret_cast<XML::XML *>(object);
        result = obj->ContainsKey(path, value);
    }

    return result;
}


void *XML_OpenFileW(const wchar_t *path, bool allow_creation) {
    void *result = nullptr;

    if (path != nullptr) {
        auto filepath = std::filesystem::path(path);
        if (std::filesystem::exists(filepath) || allow_creation) {
            result = new XML::XML(filepath);
        }
    }

    return result;
}


bool XML_SaveFileW(_In_ void *object, _In_ const wchar_t *path){
    bool result = false;

    if (object && path) {
        auto *obj = reinterpret_cast<XML::XML *>(object);
        result = obj->Save(path);
    }

    return result;
}

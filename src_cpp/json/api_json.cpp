// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <filesystem>

#include "json/api_json.h"
#include "json/json_utils.h"

using namespace OpenWG::Utils;


void *JSON_FileOpenW(const wchar_t *path, bool allow_creation) {
    void *result = nullptr;

    if(path != nullptr) {
        auto filepath = std::filesystem::path(path);
        if (std::filesystem::exists(filepath) || allow_creation) {
            result = new JSON::Json(filepath);
        }
    }

    return result;
}

bool JSON_FileClose(void *object) {
    bool result = false;

    if (object) {
        auto *obj = reinterpret_cast<JSON::Json *>(object);
        result = obj->Save();
        delete obj;
    }

    return result;
}

bool JSON_SetBoolW(void *object, const wchar_t *path, bool value) {
    bool result = false;

    if (object && path) {
        auto *obj = reinterpret_cast<JSON::Json *>(object);
        result = obj->SetBool(path, value);
    }

    return result;
}

bool JSON_SetDoubleW(void *object, const wchar_t *path, double value) {
    bool result = false;

    if (object && path) {
        auto *obj = reinterpret_cast<JSON::Json *>(object);
        result = obj->SetDouble(path, value);
    }

    return result;
}

bool JSON_SetIntegerW(void *object, const wchar_t *path, int32_t value) {
    bool result = false;

    if (object && path) {
        auto *obj = reinterpret_cast<JSON::Json *>(object);
        result = obj->SetInteger(path, value);
    }

    return result;
}

bool JSON_SetStringW(void *object, const wchar_t *path, const wchar_t* value) {
    bool result = false;

    if (object && path && value) {
        auto *obj = reinterpret_cast<JSON::Json *>(object);
        result = obj->SetString(path, value);
    }

    return result;
}

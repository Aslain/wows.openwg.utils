// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

//
// Includes
//

#include "wwise/api_wwise.h"

#include "wwise_bank.h"
#include "wwise_license.h"

using namespace OpenWG::Utils::WWISE;

//
// Globals
//

static const std::map<WwiseLicense,License> g_licenses = {
        {WwiseLicense_Unlicensed, {0x0,        0x0,        0x0,        0x0}},
        {WwiseLicense_Wargaming, {0xD2F5B297, 0xC57DA87E, 0xD10C0503, 0x6B0403D4}},
};

//
// Public
//

void *WWISE_OpenFileW(const wchar_t *path) {
    if(!path) {
        return nullptr;
    }

    auto *bank = new Bank();
    if (!bank->Read(path)) {
        delete bank;
        return nullptr;
    }

    return bank;
}

bool WWISE_Close(void* object) {
    bool result{false};
    if (object) {
        auto *obj = reinterpret_cast<Bank *>(object);
        delete obj;
        result = true;
    }
    return result;
}

int32_t WWISE_LicenseGet(void *object) {
    int32_t result = WwiseLicense_Unknown;
    if (object) {
        auto *obj = reinterpret_cast<Bank *>(object);
        SectionBKHD bkhd = obj->BKHD();
        for (auto &license: g_licenses) {
            if (bkhd.Decrypt(license.second)) {
                result = license.first;
                break;
            }
        }
    }
    return result;
}

bool WWISE_LicenseSet(void *object, int32_t license) {
    if(!object){
        return false;
    }
    if(license>2){
        return false;
    }

    auto *obj = reinterpret_cast<Bank *>(object);
    auto& bkhd = obj->BKHD();

    // decrypt if needed
    bool decrypted = bkhd.IsDecrypted();
    if(!decrypted) {
        for (auto &license: g_licenses) {
            if (bkhd.Decrypt(license.second)) {
                decrypted = true;
                break;
            }
        }
    }
    if(!decrypted) {
        return false;
    }

    if(!bkhd.Encrypt(g_licenses.at(static_cast<WwiseLicense>(license)))){
        return false;
    }

    return true;
}

bool WWISE_SaveFileW(void *object, const wchar_t *path) {
    if(!object){
        return false;
    }

    auto *obj = reinterpret_cast<Bank *>(object);
    return path ? obj->Save(path) : obj->Save();
}

bool WWISE_BKHD_ProjectId_Set(void *object, uint32_t project_id) {
    if (!object) {
        return false;
    }

    auto *obj = reinterpret_cast<Bank *>(object);
    obj->BKHD().SetProjectId(project_id);
    return true;
}

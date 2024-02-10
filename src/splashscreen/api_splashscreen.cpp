// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "splashscreen/api_splashscreen.h"
#include "splashscreen/splashscreen.h"

using namespace OpenWG::Utils::Splashscreen;

XVMEXT_API_CALL int32_t __cdecl SPLASHSCREEN_ShowSplashScreenW(const wchar_t *file_path, int32_t seconds) {
    if (!file_path) {
        return false;
    }

    SplashScreen scr;
    if (!scr.Load(file_path)) {
        return false;
    }

    return scr.Show(seconds);
}

void* SPLASHSCREEN_ShowW(_In_ const wchar_t *file_path) {
    if (!file_path) {
        return nullptr;
    }

    auto *scr = new SplashScreen();
    if (!scr->Load(file_path)) {
        delete scr;
        return nullptr;
    }

    if (!scr->Show()) {
        delete scr;
        return nullptr;
    }

    return scr;
}


bool SPLASHSCREEN_Close(void* object){
    bool result = false;

    if (object) {
        auto *obj = reinterpret_cast<SplashScreen *>(object);
        obj->Close();
        delete obj;
        result = true;
    }

    return result;
}


bool SPLASHSCREEN_CloseAfter(void* object, int msecs) {
    bool result = false;

    if (object) {
        auto* obj = reinterpret_cast<SplashScreen*>(object);
        obj->CloseAfter(msecs);
        delete obj;
        result = true;
    }

    return result;
}

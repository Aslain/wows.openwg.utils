// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "module_splashscreen/api_splashscreen.h"
#include "module_splashscreen/splashscreen.h"

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

// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "api_splashscreen.h"
#include "splashscreen.h"

XVMEXT_API_CALL bool __cdecl SPLASHSCREEN_ShowSplashScreenW(const wchar_t* file_path, int32_t seconds)
{
    if (!file_path) {
        return false;
    }

    return SplashScreen::ShowSplashScreen(file_path, seconds);
}

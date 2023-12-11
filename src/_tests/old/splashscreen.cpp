// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "module_splashscreen/api_splashscreen.h"

int main()
{
    auto path = L"F:\\Projects\\WoT\\OpenWG.Utils\\src_innosetup_demo\\splashscreen.jpg";
    bool result = SPLASHSCREEN_ShowSplashScreenW(path, 5);
    return 0;
}

// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "api_wine.h"
#include "wine.h"


XVMEXT_API_CALL bool WINE_IsRunningUnder()
{
    auto st = OpenWG::Utils::Wine::GetStatus();
    return st.running_on;
}

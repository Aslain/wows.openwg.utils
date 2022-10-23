// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <string>
#include <vector>

#include <Windows.h>

class SplashScreen
{
public:
    static bool ShowSplashScreen(const wchar_t* file_path, int seconds);
private:
    static void registerWindowClass();
    static void setSplashImage(HWND hwndSplash, HBITMAP hbmpSplash);
    static HBITMAP loadImage(const wchar_t* file_path);
    static HWND createSplashWindow();
    static void premultiplyBitmapAlpha(HDC hDC, HBITMAP hBmp);
};
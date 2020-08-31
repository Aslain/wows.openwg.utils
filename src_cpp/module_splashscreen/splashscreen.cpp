/*
* Copyright (c) 2005     , Bjarke Viksoe
* Copyright (c) 2008     , Bradley Grainger
* Copyright (c) 2017-2020, Mikhail Paulyshka.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "splashscreen.h"

#include <chrono>
#include <thread>

#include <Windows.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#include "stb_image.h"

const wchar_t windowClassName[] = L"SplashWindow";

void SplashScreen::registerWindowClass()
{
    WNDCLASSW windowClass{};
    windowClass.lpfnWndProc = DefWindowProcW;
    windowClass.lpszClassName = windowClassName;
    RegisterClassW(&windowClass);
}

void SplashScreen::premultiplyBitmapAlpha(HDC hDC, HBITMAP hBmp)
{
    BITMAP bm{};
    GetObject(hBmp, sizeof(bm), &bm);

    BITMAPINFO* bmi = (BITMAPINFO*)_alloca(sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
    ZeroMemory(bmi, sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
    bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    BOOL bRes = ::GetDIBits(hDC, hBmp, 0, bm.bmHeight, NULL, bmi, DIB_RGB_COLORS);
    if (!bRes || bmi->bmiHeader.biBitCount != 32) {
        return;
    }

    LPBYTE pBitData = (LPBYTE) LocalAlloc(LPTR, bm.bmWidth * bm.bmHeight * sizeof(DWORD));
    if (pBitData == NULL) {
        return;
    }

    LPBYTE pData = pBitData;
    GetDIBits(hDC, hBmp, 0, bm.bmHeight, pData, bmi, DIB_RGB_COLORS);
    for (int y = 0; y < bm.bmHeight; y++) {
        for (int x = 0; x < bm.bmWidth; x++) {
            pData[0] = (BYTE)((DWORD)pData[0] * pData[3] / 255);
            pData[1] = (BYTE)((DWORD)pData[1] * pData[3] / 255);
            pData[2] = (BYTE)((DWORD)pData[2] * pData[3] / 255);
            pData += 4;
        }
    }
    SetDIBits(hDC, hBmp, 0, bm.bmHeight, pBitData, bmi, DIB_RGB_COLORS);

    LocalFree(pBitData);
}

void SplashScreen::setSplashImage(HWND hwndSplash, HBITMAP hbmpSplash)
{
    // get the size of the bitmap
    BITMAP bm;
    GetObject(hbmpSplash, sizeof(bm), &bm);
    SIZE sizeSplash = { bm.bmWidth, bm.bmHeight };

    // get the primary monitor's info
    POINT ptZero = { 0 };
    HMONITOR hmonPrimary = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO monitorinfo = { 0 };
    monitorinfo.cbSize = sizeof(monitorinfo);
    GetMonitorInfoW(hmonPrimary, &monitorinfo);

    // center the splash screen in the middle of the primary work area
    const RECT& rcWork = monitorinfo.rcWork;
    POINT ptOrigin{};
    ptOrigin.x = rcWork.left + (rcWork.right - rcWork.left - sizeSplash.cx) / 2;
    ptOrigin.y = rcWork.top + (rcWork.bottom - rcWork.top - sizeSplash.cy) / 2;

    // create a memory DC holding the splash bitmap
    HDC hdcScreen = GetDC(nullptr);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hbmpOld = (HBITMAP)SelectObject(hdcMem, hbmpSplash);
    premultiplyBitmapAlpha(hdcMem, hbmpSplash);

    // use the source image's alpha channel for blending
    BLENDFUNCTION blend{};
    blend.AlphaFormat = AC_SRC_ALPHA;
    blend.BlendFlags = 0;
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;

    // paint the window (in the right location) with the alpha-blended bitmap
    UpdateLayeredWindow(hwndSplash, hdcScreen, &ptOrigin, &sizeSplash, hdcMem, &ptZero, RGB(0,0,0), &blend, ULW_ALPHA);

    // delete temporary objects
    SelectObject(hdcMem, hbmpOld);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}



HBITMAP SplashScreen::loadImage(wchar_t* file_path)
{
    int image_width = 0, image_height = 0, channels = 0;

    char buffer[500]{};
    stbi_convert_wchar_to_utf8(buffer, sizeof(buffer), file_path);

    unsigned char* data = stbi_load(buffer, &image_width, &image_height, &channels, 4);
    if (!data) {
        return nullptr;
    }

    //swap R and B channels
    for (int idx = 0; idx < image_width * image_height * channels; idx += channels){
        std::swap(data[idx], data[idx + 2]);
    }

    HBITMAP hbitmap = CreateBitmap(image_width, image_height, 1, 32, data);

    stbi_image_free(data);
    return hbitmap;
}

HWND SplashScreen::createSplashWindow()
{
    HWND hwndOwner = CreateWindowW(windowClassName, NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    return CreateWindowExW(WS_EX_LAYERED , windowClassName, NULL, WS_POPUP | WS_VISIBLE,    0, 0, 0, 0, hwndOwner, NULL, NULL, NULL);
}

bool SplashScreen::ShowSplashScreen(wchar_t* file_path, int seconds)
{
    HBITMAP bitmap = loadImage(file_path);
    if (!bitmap) {
        return false;
    }

    registerWindowClass();

    HWND hwnd = createSplashWindow();
    if (!hwnd) {
        return false;
    }

    setSplashImage(hwnd, bitmap);

    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    CloseWindow(hwnd);

    return true;
}

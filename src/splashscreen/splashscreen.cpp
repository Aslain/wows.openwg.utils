// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors
#include <thread>

#include "splashscreen/splashscreen.h"
#include "image/image_winapi.h"


namespace OpenWG::Utils::Splashscreen {
    //
    // Static
    //

    void premultiplyBitmapAlpha(HDC hDC, HBITMAP hBmp) {
        BITMAP bm{};
        GetObject(hBmp, sizeof(bm), &bm);

        BITMAPINFO *bmi = (BITMAPINFO *) _alloca(sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD)));
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
                pData[0] = (BYTE) ((DWORD) pData[0] * pData[3] / 255);
                pData[1] = (BYTE) ((DWORD) pData[1] * pData[3] / 255);
                pData[2] = (BYTE) ((DWORD) pData[2] * pData[3] / 255);
                pData += 4;
            }
        }
        SetDIBits(hDC, hBmp, 0, bm.bmHeight, pBitData, bmi, DIB_RGB_COLORS);

        LocalFree(pBitData);
    }

    //
    // SplashScreen
    //

    SplashScreen::SplashScreen() {
        registerClass();
    }

    SplashScreen::~SplashScreen() {
        Close();
        Image::FreeBitmap(m_bitmap);
    }

    bool SplashScreen::Load(const std::filesystem::path &path)
    {
        if (m_bitmap)
        {
            Image::FreeBitmap(m_bitmap);
        }
        m_bitmap = static_cast<HBITMAP>(Image::LoadToBitmap(path));
        return m_bitmap != nullptr;
    }

    bool SplashScreen::Show() {
        if (!m_bitmap) {
            return false;
        }

        if (!m_window) {
            if (!createWindow()) {
                return false;
            }
        }
        setBitmap();
        m_time = std::chrono::high_resolution_clock::now();
        return true;
    }

    bool SplashScreen::Show(int seconds) {
        if (!Show()) {
            return false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        return Close();
    }


    bool SplashScreen::Close() {
        DestroyWindow(m_window);
        m_window = nullptr;
        return true;
    }


    bool SplashScreen::CloseAfter(int msecs)
    {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_time).count() < msecs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        return Close();
    }


    bool SplashScreen::registerClass() {
        WNDCLASSW windowClass{};
        windowClass.lpfnWndProc = DefWindowProcW;
        windowClass.lpszClassName = m_className;
        return RegisterClassW(&windowClass) != 0U;
    }


    bool SplashScreen::createWindow() {
        HWND hwndOwner = CreateWindowW(m_className, nullptr, WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);
        m_window = CreateWindowExW(WS_EX_LAYERED, m_className, nullptr, WS_POPUP | WS_VISIBLE, 0, 0, 0, 0, hwndOwner,
                                   NULL, NULL, NULL);
        return m_window != nullptr;
    }

    bool SplashScreen::setBitmap() {
        // get the size of the bitmap
        BITMAP bm;
        GetObject(m_bitmap, sizeof(bm), &bm);
        SIZE sizeSplash = {bm.bmWidth, bm.bmHeight};

        // get the primary monitor's info
        POINT ptZero = {0};
        HMONITOR hmonPrimary = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
        MONITORINFO monitorinfo = {0};
        monitorinfo.cbSize = sizeof(monitorinfo);
        GetMonitorInfoW(hmonPrimary, &monitorinfo);

        // center the splash screen in the middle of the primary work area
        const RECT &rcWork = monitorinfo.rcWork;
        POINT ptOrigin{};
        ptOrigin.x = rcWork.left + (rcWork.right - rcWork.left - sizeSplash.cx) / 2;
        ptOrigin.y = rcWork.top + (rcWork.bottom - rcWork.top - sizeSplash.cy) / 2;

        // create a memory DC holding the splash bitmap
        HDC hdcScreen = GetDC(nullptr);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        HBITMAP hbmpOld = (HBITMAP) SelectObject(hdcMem, m_bitmap);
        premultiplyBitmapAlpha(hdcMem, m_bitmap);

        // use the source image's alpha channel for blending
        BLENDFUNCTION blend{};
        blend.AlphaFormat = AC_SRC_ALPHA;
        blend.BlendFlags = 0;
        blend.BlendOp = AC_SRC_OVER;
        blend.SourceConstantAlpha = 255;

        // paint the window (in the right location) with the alpha-blended bitmap
        UpdateLayeredWindow(m_window, hdcScreen, &ptOrigin, &sizeSplash, hdcMem, &ptZero, RGB(0, 0, 0), &blend,
                            ULW_ALPHA);

        // delete temporary objects
        SelectObject(hdcMem, hbmpOld);
        DeleteDC(hdcMem);
        ReleaseDC(nullptr, hdcScreen);

        return true;
    }


}

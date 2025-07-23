// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors
#include <thread>

#include "splashscreen/splashscreen.h"
#include "image/image_winapi.h"


namespace OpenWG::Utils::Splashscreen
{
    //
    // SplashScreen
    //

    SplashScreen::SplashScreen()
    {
        registerClass();
    }

    SplashScreen::~SplashScreen()
    {
        Close();
#if defined(_WIN32)
        Image::BitmapFree(m_bitmap);
#endif
    }

    bool SplashScreen::Load(const std::filesystem::path& path)
    {
#if defined(_WIN32)
        if (m_bitmap)
        {
            Image::BitmapFree(m_bitmap);
        }

        m_bitmap = Image::BitmapLoad(path);
        Image::BitmapAlphaPremultiply(m_bitmap);
#endif

        return m_bitmap != nullptr;
    }

    bool SplashScreen::Show()
    {
        if (!m_bitmap)
        {
            return false;
        }

        if (!m_window)
        {
            if (!createWindow())
            {
                return false;
            }
        }
        setBitmap();
        m_time = std::chrono::high_resolution_clock::now();
        return true;
    }

    bool SplashScreen::Show(int seconds)
    {
        if (!Show())
        {
            return false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        return Close();
    }


    bool SplashScreen::Close()
    {
#if defined(_WIN32)
        DestroyWindow(m_window);
#endif
        m_window = nullptr;
        return true;
    }


    bool SplashScreen::CloseAfter(int msecs)
    {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_time)
            .count() < msecs)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        return Close();
    }


    bool SplashScreen::registerClass()
    {
#if defined(_WIN32)
        WNDCLASSW windowClass{};
        windowClass.lpfnWndProc = DefWindowProcW;
        windowClass.lpszClassName = m_className;
        return RegisterClassW(&windowClass) != 0U;
#else
        return false;
#endif
    }


    bool SplashScreen::createWindow()
    {
#if defined(_WIN32)
        HWND hwndOwner = CreateWindowW(m_className, nullptr, WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);
        m_window = CreateWindowExW(WS_EX_LAYERED, m_className, nullptr, WS_POPUP | WS_VISIBLE, 0, 0, 0, 0, hwndOwner,
                                   NULL, NULL, NULL);
#endif

        return m_window != nullptr;
    }

    bool SplashScreen::setBitmap()
    {
#if defined(_WIN32)
        // get the size of the bitmap
        int splash_width, splash_height;
        if (!Image::BitmapGetSize(m_bitmap, &splash_width, &splash_height))
        {
            return false;
        }

        // get the primary monitor's info
        MONITORINFO monitorinfo{};
        monitorinfo.cbSize = sizeof(monitorinfo);
        if (GetMonitorInfoW(MonitorFromPoint({}, MONITOR_DEFAULTTOPRIMARY), &monitorinfo) == FALSE)
        {
            return false;
        }

        // center the splash screen in the middle of the primary work area
        const auto& rcWork = monitorinfo.rcWork;
        POINT ptOrigin{
            rcWork.left + (rcWork.right - rcWork.left - splash_width) / 2,
            rcWork.top + (rcWork.bottom - rcWork.top - splash_height) / 2
        };
        POINT ptZero{};

        // create a memory DC holding the splash bitmap
        HDC hdcScreen = GetDC(nullptr);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        HBITMAP hbmpOld = (HBITMAP)SelectObject(hdcMem, m_bitmap);

        // use the source image's alpha channel for blending
        BLENDFUNCTION blend{};
        blend.AlphaFormat = AC_SRC_ALPHA;
        blend.BlendFlags = 0;
        blend.BlendOp = AC_SRC_OVER;
        blend.SourceConstantAlpha = 255;

        // paint the window (in the right location) with the alpha-blended bitmap
        SIZE splash_size{splash_width, splash_height};
        UpdateLayeredWindow(m_window, hdcScreen, &ptOrigin, &splash_size, hdcMem, &ptZero, RGB(0, 0, 0), &blend,
                            ULW_ALPHA);

        // delete temporary objects
        SelectObject(hdcMem, hbmpOld);
        DeleteDC(hdcMem);
        ReleaseDC(nullptr, hdcScreen);
#endif

        return true;
    }
}

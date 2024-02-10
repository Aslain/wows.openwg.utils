// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

#include <Windows.h>

namespace OpenWG::Utils::Splashscreen {

    class SplashScreen {
    public:
        SplashScreen();
        ~SplashScreen();

        bool Load(const std::filesystem::path &path);

        bool Show();

        bool Show(int seconds);

        bool Close();

        bool CloseAfter(int msecs);

    private:

        bool registerClass();

        bool createWindow();

        bool setBitmap();

    private:
        HBITMAP m_bitmap{};
        HWND m_window{};
        std::chrono::high_resolution_clock::time_point m_time;

    private:
        static constexpr const wchar_t* m_className = L"SplashScreenWindow";
    };
}
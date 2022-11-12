// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <Windows.h>

namespace OpenWG::Utils::Splashscreen {

    class SplashScreen {
    public:
        SplashScreen();

        bool Load(const std::filesystem::path &path);

        bool Show(int seconds);

    private:

        bool registerClass();

        bool createWindow();

        bool setBitmap();

    private:
        HBITMAP m_bitmap{};
        HWND m_window{};

    private:
        static constexpr const wchar_t* m_className = L"SplashScreenWindow";
    };
}
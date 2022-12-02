// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "api_imagedraw.h"
#include "imagedraw.h"


extern "C" XVMEXT_API_CALL void IMAGEDRAW_PngToBmp(const wchar_t* filename)
{
    ImageDraw::PngToBmp(filename);
}
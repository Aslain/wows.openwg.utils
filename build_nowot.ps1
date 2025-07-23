#!/usr/bin/env pwsh

# Copyright (c) 2017-2021, Mikhail Paulyshka.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

Push-Location $PSScriptRoot
$root = (Get-Location).Path -replace "\\","/"

#Remove-Item -Path ./~output/ -Force -Recurse -ErrorAction SilentlyContinue

function Build-CppProject($Toolset, $Architecture) {
    New-Item -ItemType Directory -Path ./~build/$Architecture/ -ErrorAction SilentlyContinue
    Push-Location ./~build/$Architecture/ -ErrorAction Stop
    cmake -T $Toolset -A $Architecture $root/src/ -DCMAKE_INSTALL_PREFIX="$root/~output/" `
        -DBUILD_TESTS=OFF -DBUILD_MODULE_BWXML=OFF -DBUILD_MODULE_IMAGEDRAW=OFF -DBUILD_MODULE_JSON=OFF `
        -DBUILD_MODULE_NETWORK=OFF -DBUILD_MODULE_PROCESS=OFF -DBUILD_MODULE_WOT=OFF -DBUILD_MODULE_WWISE=OFF
    cmake --build . --config Release --target Install
    Pop-Location
}

Build-CppProject -Toolset v143 -Architecture Win32

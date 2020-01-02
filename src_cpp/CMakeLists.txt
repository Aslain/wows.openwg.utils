# Copyright (c) 2017-2019, Mikhail Paulyshka
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

cmake_minimum_required(VERSION 3.15)
project(xvmextensions)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(jsoncpp STATIC
  3rdparty/jsoncpp/src/lib_json/json_reader.cpp
  3rdparty/jsoncpp/src/lib_json/json_tool.h
  3rdparty/jsoncpp/src/lib_json/json_value.cpp
  3rdparty/jsoncpp/src/lib_json/json_writer.cpp
)
set_target_properties(jsoncpp PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_include_directories(jsoncpp PUBLIC 3rdparty/jsoncpp/include)


add_library(pugixml STATIC
  3rdparty/pugixml/src/pugiconfig.hpp
  3rdparty/pugixml/src/pugixml.cpp
  3rdparty/pugixml/src/pugixml.hpp
)
set_target_properties(pugixml PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_definitions(pugixml PUBLIC "-DPUGIXML_WCHAR_MODE")
target_include_directories(pugixml PUBLIC 3rdparty/pugixml/src)


add_library(lodepng STATIC
  3rdparty/lodepng/lodepng.cpp
  3rdparty/lodepng/lodepng.h
)
set_target_properties(lodepng PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_include_directories(lodepng PUBLIC 3rdparty/lodepng)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE 3rdparty/stb)

set(SOURCES_COMMON
    dllmain.cpp
    dllmain.rc

    common/api_common.cpp
    common/api_common.h
    common/encoding.cpp
    common/encoding.h
    common/filesystem.cpp
    common/filesystem.h
    common/registry.cpp
    common/registry.h
    common/string.cpp
    common/string.h
    common/vector.cpp
    common/vector.h
)
source_group("common" FILES ${SOURCES_COMMON})
option(BUILD_COMMON "Build common" ON)


set(SOURCES_JSON
    module_json/api_json.cpp
    module_json/api_json.h
    module_json/json.cpp
    module_json/json.h
)
source_group("json" FILES ${SOURCES_JSON})
option(BUILD_JSON "Build JSON" ON)

set(SOURCES_PROCESS
    module_process/api_process.cpp
    module_process/api_process.h
    module_process/process.cpp
    module_process/process.h
)
source_group("process" FILES ${SOURCES_PROCESS})
option(BUILD_PROCESS "Build Process" ON)

set(SOURCES_SPLASHSCREEN
    module_splashscreen/api_splashscreen.cpp
    module_splashscreen/api_splashscreen.h
    module_splashscreen/splashscreen.cpp
    module_splashscreen/splashscreen.h
)
source_group("splashscreen" FILES ${SOURCES_SPLASHSCREEN})
option(BUILD_SPLASHSCREEN "Build Splashscreen" ON)

set(SOURCES_WGC
    module_wgc/api_wgc.cpp
    module_wgc/api_wgc.h
    module_wgc/wgc.cpp
    module_wgc/wgc.h
)
source_group("wgc" FILES ${SOURCES_WGC})
option(BUILD_WGC "Build WGC" ON)


set(SOURCES_WINE
    module_wine/api_wine.cpp
    module_wine/api_wine.h
    module_wine/wine.cpp
    module_wine/wine.h
)
source_group("wine" FILES ${SOURCES_WINE})
option(BUILD_WINE "Build Wine" ON)

set(SOURCES_WOTFINDER
    module_wotfinder/api_wotfinder.cpp
    module_wotfinder/api_wotfinder.h
    module_wotfinder/wotclient.cpp
    module_wotfinder/wotclient.h
    module_wotfinder/wotfinder.cpp
    module_wotfinder/wotfinder.h
    module_wotfinder/wotlauncher.cpp
    module_wotfinder/wotlauncher.h
)
source_group("wotfinder" FILES ${SOURCES_WOTFINDER})
option(BUILD_WOTFINDER "Build Wotfinder" ON)

set(SOURCES_IMAGEDRAW
    module_imagedraw/api_imagedraw.cpp
    module_imagedraw/api_imagedraw.h
    module_imagedraw/imagedraw.cpp
    module_imagedraw/imagedraw.h
)
source_group("imagedraw" FILES ${SOURCES_IMAGEDRAW})
option(BUILD_IMAGEDRAW "Build ImageDraw" ON)

###############################
### Library: xvmextensions ###
###############################

add_library(xvmextensions SHARED
    ${SOURCES_COMMON}
    ${SOURCES_JSON}
    ${SOURCES_PROCESS}
	${SOURCES_SPLASHSCREEN}
    ${SOURCES_WGC}
    ${SOURCES_WINE}
    ${SOURCES_WOTFINDER}
    ${SOURCES_IMAGEDRAW}
)

target_include_directories(xvmextensions PRIVATE .)

target_link_libraries(xvmextensions PRIVATE "Version" "Kernel32" "Psapi" "Shell32" "Advapi32" "Gdi32")
target_link_libraries(xvmextensions PUBLIC jsoncpp)
target_link_libraries(xvmextensions PUBLIC pugixml)
target_link_libraries(xvmextensions PUBLIC lodepng)
target_link_libraries(xvmextensions PUBLIC stb)


if(BUILD_COMMON)
	target_compile_definitions(xvmextensions PRIVATE "-DBUILD_COMMON")
endif()

if(BUILD_JSON)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_JSON")
endif()

if(BUILD_PROCESS)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_PROCESS")
endif()

if(BUILD_SPLASHSCREEN)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_SPLASHSCREEN")
endif()

if(BUILD_WGC)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_WGC")
endif()

if(BUILD_WINE)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_WINE")
endif()

if(BUILD_WOTFINDER)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_WOTFINDER")
endif()

if(BUILD_IMAGEDRAW)
    target_compile_definitions(xvmextensions PRIVATE "-DBUILD_IMAGEDRAW")
endif()

target_compile_definitions(xvmextensions PRIVATE "-D_CRT_SECURE_NO_WARNINGS")
target_compile_definitions(xvmextensions PRIVATE "-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING")

set_target_properties(xvmextensions PROPERTIES PREFIX "")
set_target_properties(xvmextensions PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#detect platform
if(CMAKE_GENERATOR_PLATFORM STREQUAL "ARM")
    set(XVMEXT_PLAT "arm")
    set(XVMEXT_BIT "32")
elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "ARM64")
    set(XVMEXT_PLAT "arm")
    set(XVMEXT_BIT "64")
elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
    set(XVMEXT_PLAT "x86")
    set(XVMEXT_BIT "32")
elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
    set(XVMEXT_PLAT "x86")
    set(XVMEXT_BIT "64")
else()
    error("Unknown platform")
endif()


set_target_properties(xvmextensions PROPERTIES DEBUG_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
set_target_properties(xvmextensions PROPERTIES RELEASE_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(xvmextensions PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(xvmextensions PROPERTIES MINSIZEREL_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")

install(
    TARGETS xvmextensions
    RUNTIME DESTINATION bin
)

###############################
###       Test: JSON        ###
###############################

#add_executable(test_json "tests/json.cpp")
#target_link_libraries(test_json xvmextensions)
#target_include_directories(test_json PRIVATE .)

add_executable(test_process "tests/process.cpp")
target_link_libraries(test_process xvmextensions)
target_include_directories(test_process PRIVATE .)

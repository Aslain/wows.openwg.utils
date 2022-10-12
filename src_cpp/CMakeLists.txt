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

cmake_minimum_required(VERSION 3.23)
project(openwg.utils)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# JSON CPP
add_library(jsoncpp STATIC
  3rdparty/jsoncpp/src/lib_json/json_reader.cpp
  3rdparty/jsoncpp/src/lib_json/json_tool.h
  3rdparty/jsoncpp/src/lib_json/json_value.cpp
  3rdparty/jsoncpp/src/lib_json/json_writer.cpp
)
set_target_properties(jsoncpp PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_include_directories(jsoncpp PUBLIC 3rdparty/jsoncpp/include)

# PugiXML
add_library(pugixml STATIC
  3rdparty/pugixml/src/pugiconfig.hpp
  3rdparty/pugixml/src/pugixml.cpp
  3rdparty/pugixml/src/pugixml.hpp
)
set_target_properties(pugixml PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_compile_definitions(pugixml PUBLIC "-DPUGIXML_WCHAR_MODE")
target_include_directories(pugixml PUBLIC 3rdparty/pugixml/src)


# LodePNG
add_library(lodepng STATIC
  3rdparty/lodepng/lodepng.cpp
  3rdparty/lodepng/lodepng.h
)
set_target_properties(lodepng PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_include_directories(lodepng PUBLIC 3rdparty/lodepng)

# STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE 3rdparty/stb)

##############################
### Library: openwg.utils ###
##############################

add_library(openwg.utils SHARED)

target_sources(openwg.utils PRIVATE
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

    module_bwxml/api_bwxml.cpp
    module_bwxml/api_bwxml.h
    module_bwxml/BwDataDescriptor.h
    module_bwxml/BwDataElement.cpp
    module_bwxml/BwDataElement.h
    module_bwxml/BwInputStream.h
    module_bwxml/BwPackedSection.cpp
    module_bwxml/BwPackedSection.h
    module_bwxml/BwStringTable.h
    module_bwxml/BwXml.cpp
    module_bwxml/BwXml.h

    module_json/api_json.cpp
    module_json/api_json.h
    module_json/json.cpp
    module_json/json.h

    module_imagedraw/api_imagedraw.cpp
    module_imagedraw/api_imagedraw.h
    module_imagedraw/imagedraw.cpp
    module_imagedraw/imagedraw.h

    module_process/api_process.cpp
    module_process/api_process.h
    module_process/process.cpp
    module_process/process.h

    module_splashscreen/api_splashscreen.cpp
    module_splashscreen/api_splashscreen.h
    module_splashscreen/splashscreen.cpp
    module_splashscreen/splashscreen.h

    module_wgc/wgc_client.h
    module_wgc/wgc_client.cpp
    module_wgc/wgc_flavour.h
    module_wgc/wgc_finder.h
    module_wgc/wgc_finder.cpp

    module_wine/api_wine.cpp
    module_wine/api_wine.h
    module_wine/wine.cpp
    module_wine/wine.h

    module_wotfinder/api_wotfinder.cpp
    module_wotfinder/api_wotfinder.h
    module_wotfinder/wotclient.cpp
    module_wotfinder/wotclient.h
    module_wotfinder/wotfinder.cpp
    module_wotfinder/wotfinder.h
    module_wotfinder/wotlauncher.cpp
    module_wotfinder/wotlauncher.h
)


target_include_directories(openwg.utils PRIVATE .)

target_link_libraries(openwg.utils PRIVATE "Version" "Kernel32" "Psapi" "Shell32" "Advapi32" "Gdi32")
target_link_libraries(openwg.utils PUBLIC jsoncpp)
target_link_libraries(openwg.utils PUBLIC pugixml)
target_link_libraries(openwg.utils PUBLIC lodepng)
target_link_libraries(openwg.utils PUBLIC stb)

target_compile_definitions(openwg.utils PRIVATE "-DBUILD_OPENWGUTILS")
target_compile_definitions(openwg.utils PRIVATE "-D_CRT_SECURE_NO_WARNINGS")
target_compile_definitions(openwg.utils PRIVATE "-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING")

set_target_properties(openwg.utils PROPERTIES PREFIX "")
set_target_properties(openwg.utils PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#detect platform
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(XVMEXT_BIT "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(XVMEXT_BIT "32")
endif()

if(CMAKE_GENERATOR_PLATFORM STREQUAL "ARM" OR CMAKE_GENERATOR_PLATFORM STREQUAL "ARM64")
    set(XVMEXT_PLAT "arm")
else()
    set(XVMEXT_PLAT "x86")
endif()


set_target_properties(openwg.utils PROPERTIES DEBUG_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
set_target_properties(openwg.utils PROPERTIES RELEASE_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(openwg.utils PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(openwg.utils PROPERTIES MINSIZEREL_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")

install(
    TARGETS openwg.utils
    RUNTIME DESTINATION bin
)

###############################
###       Test: JSON        ###
###############################

add_executable(test_bwxml "tests/bwxml.cpp")
target_link_libraries(test_bwxml openwg.utils)
target_include_directories(test_bwxml PRIVATE .)

#add_executable(test_json "tests/json.cpp")
#target_link_libraries(test_json openwg.utils)
#target_include_directories(test_json PRIVATE .)

add_executable(test_process "tests/process.cpp")
target_link_libraries(test_process openwg.utils)
target_include_directories(test_process PRIVATE .)

add_executable(test_wot "tests/wot.cpp")
target_link_libraries(test_wot openwg.utils)
target_include_directories(test_wot PRIVATE .)
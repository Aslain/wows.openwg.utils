# SPDX-License-Identifier: MIT
# Copyright (c) 2017-2022 OpenWG.Utils Contributors

#
# CMake
#

cmake_minimum_required(VERSION 3.23)
project(openwg.utils)

include(cmake/CPM.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#
# Global options
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#
# Dependencies
#

# Catch2
CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2
    VERSION 3.3.2
)

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
CPMAddPackage(
  NAME pugixml
  GITHUB_REPOSITORY zeux/pugixml
  VERSION 1.13
  OPTIONS
    "BUILD_SHARED_LIBS OFF"
    "PUGIXML_WCHAR_MODE ON"
    "PUGIXML_STATIC_CRT ON"
)


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



#
# Library
#

add_library(openwg.utils SHARED)

file(GLOB srcs CONFIGURE_DEPENDS
        "common/*.cpp"
        "common/*.h"
        "bwxml/*.cpp"
        "bwxml/*.h"
        "imagedraw/*.cpp"
        "imagedraw/*.h"
        "json/*.cpp"
        "json/*.h"
        "json_old/*.cpp"
        "json_old/*.h"
        "process/*.cpp"
        "process/*.h"
        "splashscreen/*.cpp"
        "splashscreen/*.h"
        "string/*.cpp"
        "string/*.h"
        "wine/*.cpp"
        "wine/*.h"
        "wot/*.cpp"
        "wot/*.h"
)


target_sources(openwg.utils PRIVATE dllmain.cpp ${srcs})
target_sources(openwg.utils PRIVATE dllmain.rc)

target_include_directories(openwg.utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(openwg.utils PRIVATE "Version" "Kernel32" "Psapi" "Shell32" "Advapi32" "Gdi32")
target_link_libraries(openwg.utils PUBLIC jsoncpp)
target_link_libraries(openwg.utils PUBLIC pugixml::pugixml)
target_link_libraries(openwg.utils PUBLIC lodepng)
target_link_libraries(openwg.utils PUBLIC stb)

target_compile_definitions(openwg.utils PRIVATE "-DBUILD_OPENWGUTILS")
target_compile_definitions(openwg.utils PRIVATE "-DNOMINMAX")
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



#
# Tests
#

add_subdirectory(tests)



#
# Install
#

install(
    TARGETS openwg.utils
    RUNTIME DESTINATION bin
)

file(GLOB HEADERS_API CONFIGURE_DEPENDS  */api_*.h)
install(
    FILES ${HEADERS_API}
    DESTINATION include
)

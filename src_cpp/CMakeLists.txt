# SPDX-License-Identifier: MIT
# Copyright (c) 2017-2022 OpenWG.Utils Contributors

#
# CMake
#

cmake_minimum_required(VERSION 3.23)
project(openwg.utils)

include(cmake/cpm.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#
# Global options
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "MSVC Runtime Library")

option(BUILD_TESTS               "Build Tests"               OFF)
option(BUILD_MODULE_BWXML        "Build module BWXML"        OFF)
option(BUILD_MODULE_IMAGEDRAW    "Build module ImageDraw"    OFF)
option(BUILD_MODULE_NETWORK      "Build module Network"      OFF)
option(BUILD_MODULE_PROCESS      "Build module Process"      OFF)
option(BUILD_MODULE_SPLASHSCREEN "Build module SplashScreen" OFF)
option(BUILD_MODULE_WOT          "Build module WoT"          OFF)
option(BUILD_MODULE_WWISE        "Build module WWISE"        OFF)



#
# Dependencies
#

if(BUILD_TESTS)
  include(cmake/cpm-catch2.cmake)
endif()
include(cmake/cpm-jsoncpp.cmake)
include(cmake/cpm-lodepng.cmake)
include(cmake/cpm-pugixml.cmake)
include(cmake/cpm-stb.cmake)



#
# Library
#

add_library(openwg.utils SHARED)

target_sources(openwg.utils PRIVATE dllmain.cpp dllmain.rc)

file(GLOB srcs CONFIGURE_DEPENDS
        "common/*.cpp"
        "common/*.h"
        "fs/*.cpp"
        "fs/*.h"
        "json/*.cpp"
        "json/*.h"
        "string/*.cpp"
        "string/*.h"
        "wine/*.cpp"
        "wine/*.h"
        "xml/*.cpp"
        "xml/*.h"
)
target_sources(openwg.utils PRIVATE ${srcs})

# BWXML
if(BUILD_MODULE_BWXML)
    file(GLOB srcs CONFIGURE_DEPENDS
        "bwxml/*.cpp"
        "bwxml/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
endif()

# ImageDraw
if(BUILD_MODULE_IMAGEDRAW)
    file(GLOB srcs CONFIGURE_DEPENDS
        "imagedraw/*.cpp"
        "imagedraw/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    target_link_libraries(openwg.utils PUBLIC lodepng)
endif()

# Network
if(BUILD_MODULE_NETWORK)
    file(GLOB srcs CONFIGURE_DEPENDS
        "network/*.cpp"
        "network/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
endif()

# Process
if(BUILD_MODULE_PROCESS)
    file(GLOB srcs CONFIGURE_DEPENDS
        "process/*.cpp"
        "process/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
endif()

# Splashscreen
if(BUILD_MODULE_SPLASHSCREEN)
    file(GLOB srcs CONFIGURE_DEPENDS
        "splashscreen/*.cpp"
        "splashscreen/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    target_link_libraries(openwg.utils PUBLIC stb)
endif()


# WoT
if(BUILD_MODULE_WOT)
    file(GLOB srcs CONFIGURE_DEPENDS
        "wot/*.cpp"
        "wot/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
endif()

# WWISE
if(BUILD_MODULE_WWISE)
    file(GLOB srcs CONFIGURE_DEPENDS
        "wwise/*.cpp"
        "wwise/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
endif()




target_include_directories(openwg.utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(openwg.utils PRIVATE "Version" "Kernel32" "Psapi" "Shell32" "Advapi32" "Gdi32" "Iphlpapi" "Ws2_32")
target_link_libraries(openwg.utils PUBLIC jsoncpp_static)
target_link_libraries(openwg.utils PUBLIC pugixml::pugixml)


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
# Demo
#

if(BUILD_MODULE_WOT)
    add_subdirectory(demo)
endif()

#
# Tests
#

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()


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

# SPDX-License-Identifier: MIT
# Copyright (c) 2017-2025 OpenWG.Utils Contributors

#
# CMake
#

cmake_minimum_required(VERSION 3.23)
project(openwg.utils)

include(_cmake/cpm.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)



#
# Global options
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "MSVC Runtime Library")
set(CMAKE_POSITION_INDEPENDENT_CODE  ON)

option(BUILD_TESTS               "Build Tests"              OFF)
option(BUILD_APPS                "Build Apps"                ON)

option(BUILD_MODULE_BWXML        "Build module BWXML"        ON)
option(BUILD_MODULE_FS           "Build module FS"           ON)
option(BUILD_MODULE_IMAGE        "Build module Image"        ON)
option(BUILD_MODULE_INNO         "Build module Inno"         ON)
option(BUILD_MODULE_JSON         "Build module JSON"         ON)
option(BUILD_MODULE_NETWORK      "Build module Network"      ON)
option(BUILD_MODULE_PROCESS      "Build module Process"      ON)
option(BUILD_MODULE_SPLASHSCREEN "Build module SplashScreen" ON)
option(BUILD_MODULE_STRING       "Build module String"       ON)
option(BUILD_MODULE_WOT          "Build module WoT"          ON)
option(BUILD_MODULE_WINE         "Build module Wine"         ON)
option(BUILD_MODULE_WWISE        "Build module WWISE"        ON)
option(BUILD_MODULE_XML          "Build module XML"          ON)



#
# Library
#

add_library(openwg.utils SHARED)

file(COPY_FILE test/test_prolog.iss "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss")

# Common
file(GLOB srcs CONFIGURE_DEPENDS
        "common/*.cpp"
        "common/*.h"
        "common/*.rc"
)
target_sources(openwg.utils PRIVATE ${srcs})
file(COPY_FILE common/api_common.iss "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss")

file(READ common/test_common.iss CONTENTS)
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")

# BWXML
if(BUILD_MODULE_BWXML)
    file(GLOB srcs CONFIGURE_DEPENDS
        "bwxml/*.cpp"
        "bwxml/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})

    file(READ bwxml/api_bwxml.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ bwxml/test_bwxml.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# Wine
if(BUILD_MODULE_WINE)
    file(GLOB srcs CONFIGURE_DEPENDS
            "wine/*.cpp"
            "wine/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    
    file(READ wine/api_wine.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ wine/test_wine.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# FS
# Depends on Wine
if(BUILD_MODULE_FS)
    file(GLOB srcs CONFIGURE_DEPENDS
        "fs/*.cpp"
        "fs/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})

    file(READ fs/api_fs.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ fs/test_fs.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# Image
if(BUILD_MODULE_IMAGE)
    file(GLOB srcs CONFIGURE_DEPENDS
        "image/*.cpp"
        "image/*.h"
    )

    include(_cmake/cpm-avir.cmake)
    include(_cmake/cpm-stb.cmake)

    target_sources(openwg.utils PRIVATE ${srcs})
    target_link_libraries(openwg.utils PUBLIC stb)
    target_link_libraries(openwg.utils PUBLIC avir)

    file(READ image/api_image.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ image/test_image.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# Inno
if(BUILD_MODULE_INNO)
    file(GLOB srcs CONFIGURE_DEPENDS
            "inno/*.cpp"
            "inno/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    target_link_libraries(openwg.utils PUBLIC stb)

    file(READ inno/api_inno.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")
    
    file(READ inno/test_inno.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# JSON
if(BUILD_MODULE_JSON)
    file(GLOB srcs CONFIGURE_DEPENDS
        "json/*.cpp"
        "json/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    include(_cmake/cpm-jsoncpp.cmake)
    target_link_libraries(openwg.utils PUBLIC jsoncpp_static)

    file(READ json/api_json.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ json/test_json.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# Network
if(BUILD_MODULE_NETWORK)
    file(GLOB srcs CONFIGURE_DEPENDS
        "network/*.cpp"
        "network/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    
    file(READ network/api_network.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ network/test_network.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# String
if(BUILD_MODULE_STRING)
    file(GLOB srcs CONFIGURE_DEPENDS
        "string/*.cpp"
        "string/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    
    file(READ string/api_string.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ string/test_string.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# Process
# Depends on String
if(BUILD_MODULE_PROCESS)
    file(GLOB srcs CONFIGURE_DEPENDS
        "process/*.cpp"
        "process/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    file(READ process/api_process.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ process/test_process.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# Splashscreen
if(BUILD_MODULE_SPLASHSCREEN)
    file(GLOB srcs CONFIGURE_DEPENDS
        "splashscreen/*.cpp"
        "splashscreen/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    file(READ splashscreen/api_splashscreen.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ splashscreen/test_splashscreen.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# WoT
if(BUILD_MODULE_WOT)
    file(GLOB srcs CONFIGURE_DEPENDS
        "wot/*.cpp"
        "wot/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    
    file(READ wot/api_wot.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ wot/test_wot.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# WWISE
if(BUILD_MODULE_WWISE)
    file(GLOB srcs CONFIGURE_DEPENDS
        "wwise/*.cpp"
        "wwise/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})

    file(READ wwise/api_wwise.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ wwise/test_wwise.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

# XML
if(BUILD_MODULE_XML)
    file(GLOB srcs CONFIGURE_DEPENDS
        "xml/*.cpp"
        "xml/*.h"
    )
    target_sources(openwg.utils PRIVATE ${srcs})
    include(_cmake/cpm-pugixml.cmake)
    target_link_libraries(openwg.utils PUBLIC pugixml::pugixml)

    file(READ xml/api_xml.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

    file(READ xml/test_xml.iss CONTENTS)
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
endif()

file(READ test/test_epilog.iss CONTENTS)
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")

target_include_directories(openwg.utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

if(WIN32)
    target_link_libraries(openwg.utils PRIVATE "Version" "Kernel32" "Psapi" "Shell32" "Advapi32" "Gdi32" "Iphlpapi" "Ws2_32")
endif()

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


set_target_properties(openwg.utils PROPERTIES DEBUG_POSTFIX          ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
set_target_properties(openwg.utils PROPERTIES RELEASE_POSTFIX        ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(openwg.utils PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(openwg.utils PROPERTIES MINSIZEREL_POSTFIX     ".${XVMEXT_PLAT}_${XVMEXT_BIT}")



#
# Apps
#

if(BUILD_APPS)
    add_subdirectory(_apps)
endif()



#
# Tests
#

if(BUILD_TESTS)
  include(_cmake/cpm-catch2.cmake)
  add_subdirectory(_tests)
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

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss"
    DESTINATION innosetup
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss"
    DESTINATION test
)

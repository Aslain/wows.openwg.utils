# SPDX-License-Identifier: MIT
# Copyright (c) 2017-2022 OpenWG.Utils Contributors

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

file(GLOB srcs CONFIGURE_DEPENDS
        "common/*.cpp"
        "common/*.h"
        "module_bwxml/*.cpp"
        "module_bwxml/*.h"
        "module_imagedraw/*.cpp"
        "module_imagedraw/*.h"
        "module_json/*.cpp"
        "module_json/*.h"
        "module_process/*.cpp"
        "module_process/*.h"
        "module_splashscreen/*.cpp"
        "module_splashscreen/*.h"
        "module_wine/*.cpp"
        "module_wine/*.h"
        "module_wot/*.cpp"
        "module_wot/*.h"
)


target_sources(openwg.utils PRIVATE
    dllmain.cpp
    dllmain.rc
    ${srcs}
)


target_include_directories(openwg.utils PRIVATE .)

target_link_libraries(openwg.utils PRIVATE "Version" "Kernel32" "Psapi" "Shell32" "Advapi32" "Gdi32")
target_link_libraries(openwg.utils PUBLIC jsoncpp)
target_link_libraries(openwg.utils PUBLIC pugixml)
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

install(
    TARGETS openwg.utils
    RUNTIME DESTINATION bin
)

install(
    FILES
        module_bwxml/api_bwxml.h
        module_imagedraw/api_imagedraw.h
        module_json/api_json.h
        module_process/api_process.h
        module_splashscreen/api_splashscreen.h
        module_wine/api_wine.h
        module_wot/api_wot.h
    DESTINATION include
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

add_executable(test_splashscreen "tests/splashscreen.cpp")
target_link_libraries(test_splashscreen openwg.utils)
target_include_directories(test_splashscreen PRIVATE .)

add_executable(demo_wot "tests/splashscreen.cpp")
target_link_libraries(demo_wot openwg.utils)
target_include_directories(demo_wot PRIVATE .)

set_target_properties(demo_wot PROPERTIES DEBUG_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
set_target_properties(demo_wot PROPERTIES RELEASE_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(demo_wot PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(demo_wot PROPERTIES MINSIZEREL_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")

install(
    TARGETS demo_wot
    RUNTIME DESTINATION bin
)

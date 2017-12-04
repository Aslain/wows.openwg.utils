# Copyright (c) 2017, Mikhail Paulyshka
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

cmake_minimum_required(VERSION 3.0)
project(innoextensions)

include("ucm.cmake")
ucm_set_runtime(STATIC)

set(SOURCES_COMMON
    src/dllmain.cpp
    src/dllmain.rc

    src/common/api_common.cpp
    src/common/api_common.h
    src/common/encoding.cpp
    src/common/encoding.h
    src/common/filesystem.cpp
    src/common/filesystem.h
    src/common/process.cpp
    src/common/process.h
    src/common/registry.cpp
    src/common/registry.h
    src/common/string.cpp
    src/common/string.h
    src/common/vector.cpp
    src/common/vector.h
    src/common/wine.cpp
    src/common/wine.h
)
source_group("common" FILES ${SOURCES_COMMON})

set(SOURCES_JSON
    src/module_json/api_json.cpp
    src/module_json/api_json.h
    src/module_json/json.cpp
    src/module_json/json.h
)
source_group("json" FILES ${SOURCES_JSON})

set(SOURCES_WOTFINDER
    src/module_wotfinder/api_wotfinder.cpp
    src/module_wotfinder/api_wotfinder.h
    src/module_wotfinder/wgc.cpp
    src/module_wotfinder/wgc.h
    src/module_wotfinder/wotclient.cpp
    src/module_wotfinder/wotclient.h
    src/module_wotfinder/wotfinder.cpp
    src/module_wotfinder/wotfinder.h 
    src/module_wotfinder/wotlauncher.cpp
    src/module_wotfinder/wotlauncher.h      
)
source_group("wotfinder" FILES ${SOURCES_WOTFINDER})

set(SOURCES_3RDPARTY_JSONCPP
    src/3rdparty/jsoncpp/src/jsoncpp.cpp
)
source_group("3rdparty\\jsoncpp" FILES ${SOURCES_3RDPARTY_JSONCPP})

###############################
### Library: InnoExtensions ###
###############################
add_library(innoextensions SHARED 
    ${SOURCES_COMMON} 
    ${SOURCES_JSON}
    ${SOURCES_WOTFINDER} 
    ${SOURCES_3RDPARTY_JSONCPP}
)

target_include_directories(innoextensions PRIVATE src/3rdparty/jsoncpp/include)
target_include_directories(innoextensions PRIVATE src/3rdparty/rapidxml/include)
target_include_directories(innoextensions PRIVATE src)

target_link_libraries(innoextensions "Version" "Kernel32" "Psapi")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_COMMON")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_JSON")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_WOTFINDER")
target_compile_definitions(innoextensions PRIVATE "-D_CRT_SECURE_NO_WARNINGS")

install(
    TARGETS innoextensions
    RUNTIME DESTINATION bin
)

###############################
###       Test: JSON        ###
###############################

add_executable(test_json "src_tests/json.cpp")
target_link_libraries(test_json innoextensions)
target_include_directories(test_json PRIVATE src/3rdparty/jsoncpp/include)
target_include_directories(test_json PRIVATE src)

add_executable(test_process "src_tests/process.cpp")
target_link_libraries(test_process innoextensions)
target_include_directories(test_process PRIVATE src)

install(
    TARGETS test_json test_process
    RUNTIME DESTINATION tests
)

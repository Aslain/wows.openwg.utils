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

set(SOURCES_JSON
    module_json/api_json.cpp
    module_json/api_json.h
    module_json/json.cpp
    module_json/json.h
)
source_group("json" FILES ${SOURCES_JSON})

set(SOURCES_PROCESS
    module_process/api_process.cpp
    module_process/api_process.h
    module_process/process.cpp
    module_process/process.h
)
source_group("process" FILES ${SOURCES_PROCESS})

set(SOURCES_WGC
    module_wgc/api_wgc.cpp
    module_wgc/api_wgc.h
    module_wgc/wgc.cpp
    module_wgc/wgc.h
)
source_group("wgc" FILES ${SOURCES_WGC})


set(SOURCES_WINE
    module_wine/api_wine.cpp
    module_wine/api_wine.h
    module_wine/wine.cpp
    module_wine/wine.h
)
source_group("wine" FILES ${SOURCES_WINE})

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

set(SOURCES_IMAGEDRAW
    module_imagedraw/api_imagedraw.cpp
    module_imagedraw/api_imagedraw.h
    module_imagedraw/imagedraw.cpp
    module_imagedraw/imagedraw.h
)
source_group("imagedraw" FILES ${SOURCES_IMAGEDRAW})

set(SOURCES_3RDPARTY_JSONCPP
    3rdparty/jsoncpp/src/jsoncpp.cpp
)
source_group("3rdparty\\jsoncpp" FILES ${SOURCES_3RDPARTY_JSONCPP})

set(SOURCES_3RDPARTY_LODEPNG
    3rdparty/lodepng/src/lodepng.cpp
)
source_group("3rdparty\\lodepng" FILES ${SOURCES_3RDPARTY_LODEPNG})

###############################
### Library: InnoExtensions ###
###############################

add_library(innoextensions SHARED 
    ${SOURCES_COMMON} 
    ${SOURCES_JSON}
	${SOURCES_PROCESS}
	${SOURCES_WGC}
	${SOURCES_WINE}
    ${SOURCES_WOTFINDER}
    ${SOURCES_IMAGEDRAW}
    ${SOURCES_3RDPARTY_JSONCPP}
    ${SOURCES_3RDPARTY_LODEPNG}
)

target_include_directories(innoextensions PRIVATE 3rdparty/jsoncpp/include)
target_include_directories(innoextensions PRIVATE 3rdparty/rapidxml/include)
target_include_directories(innoextensions PRIVATE 3rdparty/lodepng/include)
target_include_directories(innoextensions PRIVATE .)

target_link_libraries(innoextensions "Version" "Kernel32" "Psapi")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_COMMON")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_JSON")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_PROCESS")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_WGC")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_WINE")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_WOTFINDER")
target_compile_definitions(innoextensions PRIVATE "-DBUILD_IMAGEDRAW")
target_compile_definitions(innoextensions PRIVATE "-D_CRT_SECURE_NO_WARNINGS")

install(
    TARGETS innoextensions
    RUNTIME DESTINATION bin
)

###############################
###       Test: JSON        ###
###############################

add_executable(test_json "tests/json.cpp")
target_link_libraries(test_json innoextensions)
target_include_directories(test_json PRIVATE 3rdparty/jsoncpp/include)
target_include_directories(test_json PRIVATE .)

add_executable(test_process "tests/process.cpp")
target_link_libraries(test_process innoextensions)
target_include_directories(test_process PRIVATE .)

install(
    TARGETS test_json test_process
    RUNTIME DESTINATION tests
)

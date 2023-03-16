###############################
###       Test: JSON        ###
###############################

add_executable(openwg.utils.test)

target_sources(openwg.utils.test PRIVATE
    test_json.cpp
    test_string.cpp
)

target_link_libraries(openwg.utils.test PRIVATE openwg.utils)
target_link_libraries(openwg.utils.test PRIVATE Catch2::Catch2WithMain)

add_custom_command(TARGET openwg.utils.test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:openwg.utils.test> $<TARGET_FILE_DIR:openwg.utils.test>
    COMMAND_EXPAND_LISTS
)

#add_executable(test_bwxml "bwxml.cpp")
#target_link_libraries(test_bwxml openwg.utils)
#target_include_directories(test_bwxml PRIVATE .)

#add_executable(test_json "json.cpp")
#target_link_libraries(test_json openwg.utils)
#target_include_directories(test_json PRIVATE .)

#add_executable(test_process "process.cpp")
#target_link_libraries(test_process openwg.utils)
#target_include_directories(test_process PRIVATE .)

#add_executable(test_splashscreen "splashscreen.cpp")
#target_link_libraries(test_splashscreen openwg.utils)
#target_include_directories(test_splashscreen PRIVATE .)

#add_executable(demo_wot "wot.cpp")
#target_link_libraries(demo_wot openwg.utils)
#target_include_directories(demo_wot PRIVATE .)

#set_target_properties(demo_wot PROPERTIES DEBUG_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
#set_target_properties(demo_wot PROPERTIES RELEASE_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
#set_target_properties(demo_wot PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
#set_target_properties(demo_wot PROPERTIES MINSIZEREL_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
#
#install(
#        TARGETS demo_wot
#        RUNTIME DESTINATION bin
#)

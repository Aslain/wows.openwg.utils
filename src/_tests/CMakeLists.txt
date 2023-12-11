###############################
###       Test: JSON        ###
###############################

add_executable(openwg.utils.test)

target_sources(openwg.utils.test PRIVATE
    test_bwxml.cpp
    test_fs.cpp
    test_json.cpp
    test_network.cpp
    test_string.cpp
    test_wwise.cpp
    test_xml.cpp
)

target_compile_definitions(openwg.utils.test PRIVATE "ASSETS_FOLDER=\"${CMAKE_CURRENT_SOURCE_DIR}/assets/\"")

target_link_libraries(openwg.utils.test PRIVATE openwg.utils)
target_link_libraries(openwg.utils.test PRIVATE Catch2::Catch2WithMain)

add_custom_command(TARGET openwg.utils.test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:openwg.utils.test> $<TARGET_FILE_DIR:openwg.utils.test>
    COMMAND_EXPAND_LISTS
)

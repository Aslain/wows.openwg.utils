###############################
###       Test: JSON        ###
###############################

add_executable(openwg.utils.demo)

target_sources(openwg.utils.demo PRIVATE
    wot.cpp
)

target_link_libraries(openwg.utils.demo PRIVATE openwg.utils)

add_custom_command(TARGET openwg.utils.demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:openwg.utils.demo> $<TARGET_FILE_DIR:openwg.utils.demo>
    COMMAND_EXPAND_LISTS
)


set_target_properties(openwg.utils.demo PROPERTIES DEBUG_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
set_target_properties(openwg.utils.demo PROPERTIES RELEASE_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(openwg.utils.demo PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
set_target_properties(openwg.utils.demo PROPERTIES MINSIZEREL_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")

install(
    TARGETS openwg.utils.demo
    RUNTIME DESTINATION bin
)

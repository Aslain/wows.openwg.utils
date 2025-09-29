###############################
###       Test: JSON        ###
###############################

function(create_app name)
  add_executable(${name})
  target_sources(${name} PRIVATE ${name}.cpp)
  target_link_libraries(${name} PRIVATE openwg.utils)
  add_custom_command(TARGET ${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${name}> $<TARGET_FILE_DIR:${name}>
    COMMAND_EXPAND_LISTS
  )


  set_target_properties(${name} PROPERTIES DEBUG_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}d")
  set_target_properties(${name} PROPERTIES RELEASE_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
  set_target_properties(${name} PROPERTIES RELWITHDEBINFO_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")
  set_target_properties(${name} PROPERTIES MINSIZEREL_POSTFIX ".${XVMEXT_PLAT}_${XVMEXT_BIT}")

  install(
      TARGETS ${name}
      RUNTIME DESTINATION bin
  )
endfunction()


create_app(owg_bwxml_unpack)
create_app(owg_wot_detect)
create_app(owg_wwise_convert_to_unlicensed)
create_app(owg_wwise_convert_to_licensed)
create_app(owg_wwise_info)
create_app(owg_wot_extract_file)
create_app(owg_wot_build_resmap)

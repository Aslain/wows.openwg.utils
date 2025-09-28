include(${CMAKE_SOURCE_DIR}/_cmake/cpm-miniz.cmake)

file(GLOB srcs CONFIGURE_DEPENDS "*.cpp" "*.h" )
target_sources(openwg.utils PRIVATE ${srcs})
target_link_libraries(openwg.utils PUBLIC miniz)

file(READ api_archive.iss CONTENTS)
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.iss" "${CONTENTS}")

file(READ test_archive.iss CONTENTS)
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/openwg.utils.test.iss" "${CONTENTS}")
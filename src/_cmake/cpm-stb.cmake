CPMAddPackage(
  NAME stb
  GITHUB_REPOSITORY nothings/stb
  GIT_TAG 5c205738c191bcb0abc65c4febfa9bd25ff35234
  VERSION 2024.11.09
  DOWNLOAD_ONLY True
)

if(stb_ADDED)
  add_library(stb INTERFACE)
  target_include_directories(stb INTERFACE "${stb_SOURCE_DIR}")
  if(WIN32)
    target_compile_definitions(stb INTERFACE "STBI_WINDOWS_UTF8")
  endif()
endif()

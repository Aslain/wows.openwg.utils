CPMAddPackage(
  NAME stb
  GITHUB_REPOSITORY nothings/stb
  GIT_TAG f0569113c93ad095470c54bf34a17b36646bbbb5
  VERSION 2025.03.14
  DOWNLOAD_ONLY True
)

if(stb_ADDED)
  add_library(stb INTERFACE)
  target_include_directories(stb INTERFACE "${stb_SOURCE_DIR}")
  if(WIN32)
    target_compile_definitions(stb INTERFACE "STBI_WINDOWS_UTF8")
  endif()
endif()

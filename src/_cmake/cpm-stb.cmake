CPMAddPackage(
  NAME stb
  GITHUB_REPOSITORY nothings/stb
  GIT_TAG 5736b15f7ea0ffb08dd38af21067c314d6a3aae9
  DOWNLOAD_ONLY True
)

if(stb_ADDED)
  add_library(stb INTERFACE)
  target_include_directories(stb INTERFACE "${stb_SOURCE_DIR}")
endif()

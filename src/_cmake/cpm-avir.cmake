CPMAddPackage(
  NAME avir
  GITHUB_REPOSITORY avaneev/avir
  GIT_TAG ae50ac8c8265d4a3e240583c423f389bf36f1f17
  VERSION 2024.02.02
  DOWNLOAD_ONLY True
)

if(avir_ADDED)
  add_library(avir INTERFACE)
  target_include_directories(avir INTERFACE "${avir_SOURCE_DIR}")
endif()

CPMAddPackage(
  NAME avir
  GITHUB_REPOSITORY avaneev/avir
  GIT_TAG 1c8433cba92695ed69903175eae0fa527d1e8bc6
  VERSION 2025.04.10
  DOWNLOAD_ONLY True
)

if(avir_ADDED)
  add_library(avir INTERFACE)
  target_include_directories(avir INTERFACE "${avir_SOURCE_DIR}")
endif()

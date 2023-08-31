CPMAddPackage(
  NAME lodepng
  GITHUB_REPOSITORY lvandeve/lodepng
  GIT_TAG c18b949b71f45e78b1f9a28c5d458bce0da505d6
  DOWNLOAD_ONLY True
)

if(lodepng_ADDED)
  add_library(lodepng STATIC
    "${lodepng_SOURCE_DIR}/lodepng.cpp"
  )
  target_include_directories(lodepng PUBLIC "${lodepng_SOURCE_DIR}")
endif()

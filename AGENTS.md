# AGENTS.md

This file provides guidance to agents when working with code in this repository.

- [option(BUILD_TESTS)](src/CMakeLists.txt:25) defaults to `OFF`; run tests from a fresh tree with `cmake -S src -B build/test -DBUILD_TESTS=ON && cmake --build build/test --target openwg.utils.test && ctest --test-dir build/test --output-on-failure` to pick up the Catch2 harness defined in [src/_tests/CMakeLists.txt](src/_tests/CMakeLists.txt:5).
- [build.ps1](build.ps1:55) invokes `iscc` twice after the CMake install step, so Inno Setup’s compiler must be on `PATH` before using the stock build scripts.
- Module installers are assembled by concatenating plain-text `.iss` fragments via `file(READ)`/`file(APPEND)` in [src/CMakeLists.txt](src/CMakeLists.txt:65); keep new scripts ASCII (no BOM) and free of conditional directives that would break naive concatenation.
- JSON paths are validated to start with `/` in [JSON::SetValue](src/json/json_utils.cpp:83), and the tests show bare keys being rejected ([src/_tests/test_json.cpp](src/_tests/test_json.cpp:158)); always prepend a slash when calling the public JSON setters.
- [JSON::~Json()](src/json/json_utils.cpp:30) always calls `Save()`, so leaked handles still flush to disk—explicitly close anything you open in long-lived tools to avoid surprise rewrites.
- The wide-string constructor for JSON wraps inputs lacking braces ([JSON::Json(const wchar_t*)](src/json/json_utils.cpp:19)), so quick experiments can feed raw key/value pairs but will be persisted under an implicit root object.
- The Inno test harness opens `{src}/test_result.json` through [test_prolog.iss](src/test/test_prolog.iss:60); running the generated installer outside a writable checkout will fail silently because the JSON call can’t create its target.
- [STRING_LoadFromFile](src/string/api_string.iss:17) sizes its buffer as `FS_FileSize * 2` before retrying, assuming UTF-16 expansion; keep DLL implementations returning byte counts or the Inno wrapper will truncate.
- [String::ReplaceRegex](src/string/string.cpp:162) auto-escapes `{`/`}` before compiling a regex, so patterns that rely on quantifier braces must already be escaped when they enter the API.
- [FS_Search_QueryFolderW](src/fs/fs_search.cpp:15) iterates every logical drive and recurses until `max_depth`; clamp the depth when exposing this to UI code or you will traverse entire disks.
- The toolchain is fixed to C++23 with a static MSVC runtime via [set(CMAKE_CXX_STANDARD 23)](src/CMakeLists.txt:20) and [set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded…")](src/CMakeLists.txt:22); match those flags when adding external targets to avoid runtime mismatches.
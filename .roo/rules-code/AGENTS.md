# AGENTS.md

This file provides guidance to agents when working with code in this repository.

- JSON handles auto-flush on destruction ([JSON::~Json()](src/json/json_utils.cpp:30)); always pair `JSON_Close` with every `JSON_Open*` in long-lived tools or you will persist intermediate state.
- JSON mutation helpers reject bare keys ([JSON::SetValue](src/json/json_utils.cpp:83)); prepend `/` before handing paths into the DLL-facing wrappers and Inno scripts.
- Wide-string JSON constructors silently wrap payloads without braces ([JSON::Json(const wchar_t*)](src/json/json_utils.cpp:19)); normalize inputs before diffing serialized output.
- Regex helpers escape `{`/`}` internally ([String::ReplaceRegex](src/string/string.cpp:162)); supply already-escaped quantifiers when you need raw brace semantics.
- Inno wrappers assume string buffers sized to `FS_FileSize * 2` ([STRING_LoadFromFile](src/string/api_string.iss:17)); keep native exports returning byte counts so the retry path can resize correctly.
- Filesystem search walks every logical drive when `max_depth` is large ([FS_Search_QueryFolderW](src/fs/api_fs.cpp:42)); clamp depth before exposing the API to UI surfaces to avoid recursive drive scans.
- Module API stubs are merged into installers at CMake configure time ([file(APPEND) pipeline](src/CMakeLists.txt:65)); keep new `.iss` fragments ASCII without conditional directives to preserve concatenation order.
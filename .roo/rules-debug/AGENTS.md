# AGENTS.md

This file provides guidance to agents when working with code in this repository.

- The Inno test harness writes into `{src}/test_result.json` via `TEST_Start`/`TEST_Finish` ([src/test/test_prolog.iss](src/test/test_prolog.iss:59)); debugging installers outside the workspace fails because the JSON backend cannot create that file.
- JSON handles flush on destruction ([JSON::~Json()](src/json/json_utils.cpp:30)); when debugging leaks, remember that unclosed handles still persist last mutations to disk.
- Filesystem discovery fans out across every logical drive until `max_depth` ([FS_Search_QueryFolderW](src/fs/api_fs.cpp:42)); clamp depth during repros or you’ll get multi-minute traversals that look like hangs.
- Inno wrappers double the buffer size on the first call ([STRING_LoadFromFile](src/string/api_string.iss:22)); if native functions stop reporting byte counts, downstream retries spin without progress—check return codes before chasing UI symptoms.
# AGENTS.md

This file provides guidance to agents when working with code in this repository.

- The monolithic `openwg.utils` DLL is assembled by toggling module flags in [src/CMakeLists.txt](src/CMakeLists.txt:28); every subsystem (archive, string, wwise, etc.) contributes sources and injects installer/test fragments through `file(APPEND)` calls, so treat modules as plug-ins sharing a single binary and C ABI.
- Inno integration depends on the generated stubs `openwg.utils.iss` and `openwg.utils.test.iss` created at configure time ([src/CMakeLists.txt](src/CMakeLists.txt:65)); adding a module requires providing both runtime and test `.iss` fragments or the build pipeline emits incomplete installers.
- The Catch2 test executable links against the same DLL and copies its runtime dependencies post-build ([src/_tests/CMakeLists.txt](src/_tests/CMakeLists.txt:24)); expanding module APIs without updating the shared library will break tests and installers simultaneously.
- All public exports use the `XVMEXT_API_CALL` macro ([src/common/api_common.h](src/common/api_common.h:13)), ensuring consistent `__declspec(dllexport)` usage; new ABI-facing headers must include it or downstream Inno/C# bindings will fail to resolve symbols.
# XVM.Extensions

[![Build status](https://ci.appveyor.com/api/projects/status/4am9m44gggbcnr8f?svg=true)](https://ci.appveyor.com/project/MikhailPaulyshka/xfw-extensionlib)

A set of tools that help in the development of modpacks and other WoT-related applications.

This project provides several ways to use it features:

* C API
* C# assembly
* InnoSetup script

## Feature matrix

| Function                       | C    | C#                   | InnoSetup |
| ------------------------------ | ---- | -------------------- | --------- |
| BwXML::Unpack                  | ✅    | ✅                    | ✅         |
| JSON::ContainsKey              | ✅    | ❌                    | ✅         |
| JSON::GetValue                 | ✅    | ❌                    | ✅         |
| JSON::SetValueBool             | ✅    | ❌                    | ✅         |
| JSON::SetValueObj              | ✅    | ❌                    | ✅         |
| JSON::GetNamesAndValues        | ✅    | ❌                    | ✅         |
| JSON::GetNamesAndValues_S      | ✅    | ❌                    | ✅         |
| JSON::GetArrayValue_S          | ✅    | ❌                    | ✅         |
| ImageDraw::PngToBmp            | ✅    | ❌                    | ✅         |
| Process::GetRunningInDirectory | ✅    | ✅                    | ✅         |
| Process::TerminateProcess      | ✅    | ✅                    | ✅         |
| SplashScreen::ShowSplashScreen | ✅    | ✅                    | ✅         |
| WGC::GetInstallPath            | ✅    | ✅                    | ✅         |
| WGC::IsInstalled               | ✅    | ✅                    | ✅         |
| Wine::IsRunningUnder           | 🐍    | 🐍                    | 🐍         |
| WOT::AddClient                 | ✅    | ❌                    | ✅         |
| WOT::GetPreferredClientPath    | ✅    | ✅                    | ✅         |
| WOT::GetClientsCount           | ✅    | ✅                    | ✅         |
| WOT::GetClientBranch           | ✅    | ✅                    | ✅         |
| WOT::GetClientType             | ✅    | ✅                    | ✅         |
| WOT::GetClientLocale           | ✅    | ✅                    | ✅         |
| WOT::GetClientPath             | ✅    | ✅                    | ✅         |
| WOT::GetClientVersion          | ✅    | ✅                    | ✅         |
| WOT::GetClientExeVersion       | ✅    | ✅                    | ✅         |
| WOT::GetIdsRangeForRegion      | ❌    | ✅                    | ❌         |
| WOT::GetRegionFromString       | ❌    | ✅                    | ❌         |
| XVM::GetLatestVersion          | ❌    | 🐍<sup>.NET 4.5</sup> | ❌         |
| XVM::GetVersion                | ❌    | 🐍<sup>.NET 4.5</sup> | ❌         |


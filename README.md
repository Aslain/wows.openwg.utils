# OpenWG.Utils.Installer

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
| Wine::IsRunningUnder           | 🐍    | 🐍                    | 🐍         |
| WOT::AddClient                 | ✅    | ❌                    | ✅         |
| WOT::GetPreferredClientPath    | ✅    | ✅                    | ✅         |
| WOT::GetClientsCount           | ✅    | ✅                    | ✅         |
| WOT::GetClientBranch           | ✅    | ✅                    | ✅         |
| WOT::GetClientType             | ✅    | ✅                    | ✅         |
| WOT::GetClientWgcFlavour       | ✅    | ❌                    | ✅         |
| WOT::GetClientLocale           | ✅    | ✅                    | ✅         |
| WOT::GetClientPath             | ✅    | ✅                    | ✅         |
| WOT::GetClientVersion          | ✅    | ✅                    | ✅         |
| WOT::GetClientExeVersion       | ✅    | ✅                    | ✅         |
| WOT::GetIdsRangeForRegion      | ❌    | ✅                    | ❌         |
| WOT::GetRegionFromString       | ❌    | ✅                    | ❌         |

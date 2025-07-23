// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2025 OpenWG.Utils Contributors

#define APP_WEBSITE    "https://gitlab.com/openwg/openwg.utils"
#define APP_VERSION    "25.7.23.1"
#define APP_DIR_UNINST "openwg_uninst_test"

#define OPENWGUTILS_LANG_RU 0
#define OPENWGUTILS_DIR_SRC    "..\bin"
#define OPENWGUTILS_DIR_UNINST APP_DIR_UNINST

#include "..\innosetup\openwg.utils.iss"

[Setup]
AppCopyright    = "2017-2025 © OpenWG Contributors"
AppId           = {{f1810aeb-356e-4b4d-aa6a-b380f67b1a9f}
AppName         = OpenWG Utils Test
AppPublisher    = OpenWG Contributors
AppPublisherURL = {#APP_WEBSITE}
AppSupportURL   = {#APP_WEBSITE}
AppUpdatesURL   = {#APP_WEBSITE}
AppVersion      = {#APP_VERSION}

WizardStyle          = modern

Compression=lzma2/ultra64
InternalCompressLevel=ultra64

DirExistsWarning=false
CreateAppDir=true
AppendDefaultDirName=false
ShowLanguageDialog=true
DisableProgramGroupPage=true
Uninstallable=true
DisableDirPage=false

OutputDir=.
OutputBaseFilename=openwg_utils_test

UninstallFilesDir={app}\{#APP_DIR_UNINST}
DefaultDirName=C:\
UsePreviousAppDir=yes

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl";

[Code]

var
    g_test_json: Integer;

procedure TEST_SetResult(TestName: String; Value: Boolean);
begin
    JSON_SetBool(g_test_json, TestName, Value);
end;


procedure TEST_Start();
begin
    g_test_json := JSON_OpenFile(ExpandConstant('{src}/test_result.json'), True);
end;


procedure TEST_Finish();
begin
    JSON_Close(g_test_json);
end;

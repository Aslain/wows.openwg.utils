// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#define APP_WEBSITE    "https://gitlab.com/openwg/openwg.utils"
#define APP_VERSION    "2022.11.12.2"
#define APP_DIR_UNINST "openwg_utils\uninst"

#define OPENWGUTILS_DIR_SRC    "..\bin"
#define OPENWGUTILS_DIR_UNINST APP_DIR_UNINST

#include "..\innosetup\openwg.utils.iss"

[Setup]
AppCopyright    = "2022 © OpenWG Contributors"
AppId           = {{f1810aeb-356e-4b4d-aa6a-b380f67b1a9e}
AppName         = OpenWG Utils Demo
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
OutputBaseFilename=openwg_utils_demo

UninstallFilesDir={app}\{#APP_DIR_UNINST}
DefaultDirName=C:\


[Run]
Filename: {#APP_WEBSITE}; Description: "{cm:open_website}"; Flags: postinstall nowait shellexec;



[Components]
Name: "test_component"; Description: "Test Component"; Types: full compact custom;



[Files]
Source: "test.txt"; DestDir: "{app}"
Source: "test_component.txt"; DestDir: "{app}"; Components: test_component



[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl";
Name: "ru"; MessagesFile: "compiler:Languages/Russian.isl";



[CustomMessages]
en.open_website=Open Website
ru.open_website=Открыть сайт



[Code]

var
  WotList: TNewComboBox;

procedure InitializeWizard();
begin
  WotList := WotList_Create(WizardForm.DirEdit.Parent,
      WizardForm.DirEdit.Left,
      WizardForm.DirEdit.Top,
      WizardForm.DirBrowseButton.Left + WizardForm.DirBrowseButton.Width,
      WizardForm.DirEdit.Height
  );
  WizardForm.DirEdit.Visible := False;
  WizardForm.DirEdit.Text := '';
  WizardForm.DirBrowseButton.Visible := False;
end;

procedure CurPageChanged(CurPage: Integer);
begin
  if (CurPage = wpSelectDir) then
  begin
    if WotList.ItemIndex = -1 then
    begin
      WotList.ItemIndex := 0;
    end;

    WotList.OnChange(nil);
  end;
end;

function NextButtonClick(CurPage: Integer): Boolean;
begin
  Result := True;

  if (CurPage = wpSelectDir) then
  begin
    if not FileExists(ExpandConstant('{app}\WorldOfTanks.exe')) then
    begin
      MsgBox(ExpandConstant('{cm:wotNotFound}'), mbError, MB_OK);
      Result := False;
      Exit;
    end;
  end;
end;

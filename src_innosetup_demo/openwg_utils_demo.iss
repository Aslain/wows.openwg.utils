// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#define APP_WEBSITE    "https://gitlab.com/openwg/openwg.utils"
#define APP_VERSION    "2022.11.12.4"
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
Name: "filecheck"      ; Description: "Filecheck"    ; Types: full compact custom;

Name: "test"           ; Description: "Test"         ; Types: full compact custom;
Name: "test/lesta"     ; Description: "Test / Lesta" ; Types: full compact custom;
Name: "test/lesta/sub" ; Description: "Sub"          ; Types: full compact custom
Name: "test/wg"        ; Description: "Test / WG"    ; Types: full compact custom;
Name: "test/wg/sub"    ; Description: "Sub"          ; Types: full compact custom;


[Files]
Source: "splashscreen.png"; Flags: dontcopy noencryption

Source: "filecheck.txt"       ; DestDir: "{app}/tests/filecheck"; Components: filecheck
Source: "filecheck_lesta.txt" ; DestDir: "{app}/tests/filecheck"; Components: filecheck; Check: Check_IsLesta
Source: "filecheck_wg.txt"    ; DestDir: "{app}/tests/filecheck"; Components: filecheck; Check: not Check_IsLesta

Source: "test.txt"            ; DestDir: "{app}/tests/test"; Components: test
Source: "test_lesta.txt"      ; DestDir: "{app}/tests/test"; Components: test/lesta
Source: "test_lesta_sub.txt"  ; DestDir: "{app}/tests/test"; Components: test/lesta/sub
Source: "test_wg.txt"         ; DestDir: "{app}/tests/test"; Components: test/wg
Source: "test_wg_sub.txt"     ; DestDir: "{app}/tests/test"; Components: test/wg/sub


[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl";
Name: "ru"; MessagesFile: "compiler:Languages/Russian.isl";



[CustomMessages]
en.open_website=Open Website
ru.open_website=Открыть сайт



[Code]

//
// Globals
//

var
  WotList: TNewComboBox;



//
// Initialize
//

function InitializeSetup: Boolean;
begin
    ExtractTemporaryFile('splashscreen.png');
    SPLASHSCREEN_ShowSplashScreenW('splashscreen.png', 3);
    Result := True;
end;


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



//
// CurPageChanged
//

procedure CurPageChanged_wpSelectDir();
begin
  if WotList.ItemIndex = -1 then
  begin
    WotList.ItemIndex := 0;
  end;

  WotList.OnChange(WotList);
end;


procedure CurPageChanged_wpSelectComponents();
var
  Index: Integer;
  IsLesta: Boolean;
  ItemCaption: String;
begin
  IsLesta := WotList_Selected_Lesta(WotList);

  for Index := 0 to WizardForm.ComponentsList.Items.Count - 1 do
  begin
    ItemCaption := WizardForm.ComponentsList.ItemCaption[Index];
    if ((pos('Lesta', ItemCaption) <> 0) and (not IsLesta)) or ((pos('WG', ItemCaption) <> 0) and IsLesta) then
    begin
        WizardForm.ComponentsList.Checked[Index] := false; 
        WizardForm.ComponentsList.ItemEnabled[Index] := false;   
    end;
  end;
end;


procedure CurPageChanged(CurPage: Integer);
begin
  if (CurPage = wpSelectDir) then
  begin
    CurPageChanged_wpSelectDir();
  end;

  if (CurPage = wpSelectComponents) then
  begin
    CurPageChanged_wpSelectComponents();
  end
end;



//
// NextButtonClick
//

function NextButtonClick_wpSelectDir(): Boolean;
begin
  if not FileExists(ExpandConstant('{app}\WorldOfTanks.exe')) then
  begin
    MsgBox(ExpandConstant('{cm:wotNotFound}'), mbError, MB_OK);
    Result := False;
    Exit;
  end;
end;


function NextButtonClick(CurPage: Integer): Boolean;
begin
  Result := True;

  if (CurPage = wpSelectDir) then
  begin
    Result := NextButtonClick_wpSelectDir();
  end;
end;


//
// Checks
//

function Check_IsLesta(): Boolean;
begin
  Result := WotList_Selected_Lesta(WotList);
end;

// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#define APP_WEBSITE    "https://gitlab.com/openwg/openwg.utils"
#define APP_VERSION    "2022.11.28.1"
#define APP_DIR_UNINST "openwg_uninst"

#define WOT_VERSION_PATTERN "1.18.1.*"

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
UsePreviousAppDir=yes


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
Source: "assets/splashscreen.png"; Flags: dontcopy noencryption
Source: "assets/splashscreen_uninst.png"; DestDir: "{app}/{#APP_DIR_UNINST}"; Flags: noencryption

Source: "cur_ver/mods.txt"         ; DestDir: "{app}/{code:PH_Folder_Mods}/"
Source: "cur_ver/res_mods.txt"     ; DestDir: "{app}/{code:PH_Folder_Resmods}/"

Source: "test/filecheck.txt"       ; DestDir: "{app}/mods/openwg_test"; Components: filecheck
Source: "test/filecheck_lesta.txt" ; DestDir: "{app}/mods/openwg_test"; Components: filecheck; Check: CHECK_IsLesta
Source: "test/filecheck_wg.txt"    ; DestDir: "{app}/mods/openwg_test"; Components: filecheck; Check: not CHECK_IsLesta
Source: "test/test.txt"            ; DestDir: "{app}/mods/openwg_test"; Components: test
Source: "test/test_lesta.txt"      ; DestDir: "{app}/mods/openwg_test"; Components: test/lesta
Source: "test/test_lesta_sub.txt"  ; DestDir: "{app}/mods/openwg_test"; Components: test/lesta/sub
Source: "test/test_wg.txt"         ; DestDir: "{app}/mods/openwg_test"; Components: test/wg
Source: "test/test_wg_sub.txt"     ; DestDir: "{app}/mods/openwg_test"; Components: test/wg/sub


[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl";
Name: "ru"; MessagesFile: "compiler:Languages/Russian.isl";



[CustomMessages]
en.open_website=Open Website
ru.open_website=Открыть сайт
en.version_not_match=This client is not supported.%n%nThis installer only supports WoT v{#WOT_VERSION_PATTERN}
ru.version_not_match=Выбранный клиент не поддерживается.%n%nЭтот установщик поддерживает только WoT v{#WOT_VERSION_PATTERN}



[Code]

//
// Globals
//

var
  WotList: TNewComboBox;


//
// Checks
//

function CHECK_IsLesta(): Boolean;
var
  Flavour: Integer;
begin
  Flavour := WotList_Selected_Record(WotList).LauncherFlavour
  Result := Flavour = 4;
end;



//
// Placeholders
//

function PH_Folder_Mods(s: String): String;
begin
  Result := WotList_Selected_Record(WotList).PathMods;
end;

function PH_Folder_Resmods(s: String): String;
begin
  Result := WotList_Selected_Record(WotList).PathResmods;
end;



//
// Initialize
//

function InitializeSetup: Boolean;
begin
  ExtractTemporaryFile('splashscreen.png');
  SPLASHSCREEN_ShowSplashScreenW('splashscreen.png', 3);
  Result := True;
end;


function InitializeUninstall: Boolean;
begin
  SPLASHSCREEN_ShowSplashScreenW(ExpandConstant('{app}\{#APP_DIR_UNINST}\splashscreen_uninst.png'), 3);
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
  WotList.ItemIndex := WOT_ClientFind(WizardForm.DirEdit.Text);

  if (WotList.ItemIndex = -1) and (WotList.Items.Count > 1) then
    WotList.ItemIndex := 0;
  WotList.OnChange(WotList);

  WizardForm.DirEdit.Visible := False;
  WizardForm.DirBrowseButton.Visible := False;
end;



//
// CurPageChanged
//

procedure CurPageChanged_wpSelectDir();
begin
end;


procedure CurPageChanged_wpSelectComponents();
var
  Index: Integer;
  IsLesta: Boolean;
  ItemCaption: String;
begin
  IsLesta := CHECK_IsLesta();

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
  case CurPage of
    wpSelectDir: CurPageChanged_wpSelectDir();
    wpSelectComponents: CurPageChanged_wpSelectComponents();
  end
end;



//
// CurUninstallStepChanged
//

procedure CurUninstallStepChanged_usUninstall();
begin
  OPENWG_DllUnload();
  OPENWG_DllDelete();
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  case CurUninstallStep of
    usUninstall: CurUninstallStepChanged_usUninstall();
  end
end;



//
// DeinitializeUninstall
//

procedure DeinitializeUninstall();
begin
end;



//
// NextButtonClick
//

function NextButtonClick_wpSelectDir(): Boolean;
begin
  if not WotList_Selected_VersionMatch(WotList, '{#WOT_VERSION_PATTERN}') then
  begin
    MsgBox(ExpandConstant('{cm:version_not_match}'), mbError, MB_OK);
    Result := False;
    Exit;
  end;
end;


function NextButtonClick(CurPage: Integer): Boolean;
begin
  Result := True;

  case CurPage of
    wpSelectDir: Result := NextButtonClick_wpSelectDir();
  end;
end;


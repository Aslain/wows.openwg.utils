


//
// WOT
//

[CustomMessages]
en.openwg_browse=Browse...
ru.openwg_browse=Обзор...
en.openwg_client_not_found=The game client was not detected in the specified folder.
ru.openwg_client_not_found=В указанной папке клиент игры не был обнаружен.
en.openwg_unknown=Unknown
ru.openwg_unknown=Неизвестно
en.openwg_branch_release=Release
ru.openwg_branch_release=Релиз
en.openwg_branch_ct=Common Test
ru.openwg_branch_ct=Общий тест
en.openwg_branch_st=Super Test
ru.openwg_branch_st=Супертест
en.openwg_branch_sb=Sandbox
ru.openwg_branch_sb=Песочница

[Code]

type
  ClientRecord = Record
    Index: Integer;
    Branch: Integer;
    LauncherFlavour: Integer;
    Locale: String;
    Path: String;
    PathMods: String;
    PathResmods: String;
    Realm: String;
    ContentType: Integer;
    Version: String;
    VersionExe: String;
  end;

// WOT/AddClientW
function WOT_AddClientW_I(ClientPath: String): Integer;
external 'WOT_AddClientW@files:openwg.utils.dll cdecl setuponly';

function WOT_AddClientW_U(ClientPath: String): Integer;
external 'WOT_AddClientW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_AddClientW(ClientPath: String): Integer;
begin
    if IsUninstaller() then
        Result := WOT_AddClientW_U(ClientPath)
    else
        Result := WOT_AddClientW_I(ClientPath)
end;


// WOT/LauncherGetPreferredClient
function WOT_LauncherGetPreferredClient_I(LauncherFlavour: Integer): Integer;
external 'WOT_LauncherGetPreferredClient@files:openwg.utils.dll cdecl setuponly';

function WOT_LauncherGetPreferredClient_U(LauncherFlavour: Integer): Integer;
external 'WOT_LauncherGetPreferredClient@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_LauncherGetPreferredClient(LauncherFlavour: Integer): Integer;
begin
    if IsUninstaller() then
        Result := WOT_LauncherGetPreferredClient_U(LauncherFlavour)
    else
        Result := WOT_LauncherGetPreferredClient_I(LauncherFlavour)
end;


// WOT/LauncherRescan
function WOT_LauncherRescan_I(): Integer;
external 'WOT_LauncherRescan@files:openwg.utils.dll cdecl setuponly';

function WOT_LauncherRescan_U(): Integer;
external 'WOT_LauncherRescan@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_LauncherRescan(): Integer;
begin
    if IsUninstaller() then
        Result := WOT_LauncherRescan_U()
    else
        Result := WOT_LauncherRescan_I()
end;


// WOT/LauncherSetDefault
function WOT_LauncherSetDefault_I(LauncherFlavour: Integer): Integer;
external 'WOT_LauncherSetDefault@files:openwg.utils.dll cdecl setuponly';

function WOT_LauncherSetDefault_U(LauncherFlavour: Integer): Integer;
external 'WOT_LauncherSetDefault@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_LauncherSetDefault(LauncherFlavour: Integer): Integer;
begin
    if IsUninstaller() then
        Result := WOT_LauncherSetDefault_U(LauncherFlavour)
    else
        Result := WOT_LauncherSetDefault_I(LauncherFlavour)
end;


// WOT/ClientFind
function WOT_ClientFind_I(Path: String): Integer;
external 'WOT_ClientFind@files:openwg.utils.dll cdecl setuponly';

function WOT_ClientFind_U(Path: String): Integer;
external 'WOT_ClientFind@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_ClientFind(Path: String): Integer;
begin
    if IsUninstaller() then
        Result := WOT_ClientFind_U(Path)
    else
        Result := WOT_ClientFind_I(Path)
end;


// WOT/ClientIsStarted
function WOT_ClientIsStarted_I(ClientIndex: Integer): Integer;
external 'WOT_ClientIsStarted@files:openwg.utils.dll cdecl setuponly';

function WOT_ClientIsStarted_U(ClientIndex: Integer): Integer;
external 'WOT_ClientIsStarted@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_ClientIsStarted(ClientIndex: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := WOT_ClientIsStarted_U(ClientIndex) = 1
    else
        Result := WOT_ClientIsStarted_I(ClientIndex) = 1
end;


// WOT/ClientIsVersionMatch
function WOT_ClientIsVersionMatch_I(ClientIndex: Integer; VersionPattern: String): Integer;
external 'WOT_ClientIsVersionMatch@files:openwg.utils.dll cdecl setuponly';

function WOT_ClientIsVersionMatch_U(ClientIndex: Integer; VersionPattern: String): Integer;
external 'WOT_ClientIsVersionMatch@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_ClientIsVersionMatch(ClientIndex: Integer; VersionPattern: String): Boolean;
begin
    if IsUninstaller() then
        Result := WOT_ClientIsVersionMatch_U(ClientIndex, VersionPattern) = 1
    else
        Result := WOT_ClientIsVersionMatch_I(ClientIndex, VersionPattern) = 1
end;


// WOT/ClientTerminate
function WOT_ClientTerminate_I(ClientIndex: Integer): Integer;
external 'WOT_ClientTerminate@files:openwg.utils.dll cdecl setuponly';

function WOT_ClientTerminate_U(ClientIndex: Integer): Integer;
external 'WOT_ClientTerminate@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_ClientTerminate(ClientIndex: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := WOT_ClientTerminate_U(ClientIndex) = 1
    else
        Result := WOT_ClientTerminate_I(ClientIndex) = 1
end;


// WOT/GetClientsCount
function WOT_GetClientsCount_I(): Integer;
external 'WOT_GetClientsCount@files:openwg.utils.dll cdecl setuponly';

function WOT_GetClientsCount_U(): Integer;
external 'WOT_GetClientsCount@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientsCount(): Integer;
begin
    if IsUninstaller() then
        Result := WOT_GetClientsCount_U()
    else
        Result := WOT_GetClientsCount_I()
end;


// WOT/GetClientBranch
function WOT_GetClientBranch_I(ClientIndex: Integer): Integer;
external 'WOT_GetClientBranch@files:openwg.utils.dll cdecl setuponly';

function WOT_GetClientBranch_U(ClientIndex: Integer): Integer;
external 'WOT_GetClientBranch@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientBranch(ClientIndex: Integer): Integer;
begin
    if IsUninstaller() then
        Result := WOT_GetClientBranch_U(ClientIndex)
    else
        Result := WOT_GetClientBranch_I(ClientIndex)
end;


// WOT/GetClientLauncherFlavour
function WOT_GetClientLauncherFlavour_I(ClientIndex: Integer): Integer;
external 'WOT_GetClientLauncherFlavour@files:openwg.utils.dll cdecl setuponly';

function WOT_GetClientLauncherFlavour_U(ClientIndex: Integer): Integer;
external 'WOT_GetClientLauncherFlavour@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientLauncherFlavour(ClientIndex: Integer): Integer;
begin
    if IsUninstaller() then
        Result := WOT_GetClientLauncherFlavour_U(ClientIndex)
    else
        Result := WOT_GetClientLauncherFlavour_I(ClientIndex)
end;


// WOT/GetClientLocale
procedure WOT_GetClientLocaleW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientLocaleW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientLocaleW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientLocaleW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientLocaleW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientLocaleW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientLocaleW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// WOT/GetClientPathW
procedure WOT_GetClientPathW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientPathW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientPathW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientPathW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientPathW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// WOT/GetClientPathModsW
procedure WOT_GetClientPathModsW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathModsW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientPathModsW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathModsW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientPathModsW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientPathModsW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientPathModsW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// WOT/GetClientPathResmodsW
procedure WOT_GetClientPathResmodsW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathResmodsW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientPathResmodsW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathResmodsW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientPathResmodsW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientPathResmodsW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientPathResmodsW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// WOT/GetClientRealmW
procedure WOT_GetClientRealmW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientRealmW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientRealmW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientRealmW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientRealmW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientRealmW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientRealmW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// WOT/GetClientType
function WOT_GetClientType_I(ClientIndex: Integer): Integer;
external 'WOT_GetClientType@files:openwg.utils.dll cdecl setuponly';

function WOT_GetClientType_U(ClientIndex: Integer): Integer;
external 'WOT_GetClientType@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientType(ClientIndex: Integer): Integer;
begin
    if IsUninstaller() then
        Result := WOT_GetClientType_U(ClientIndex)
    else
        Result := WOT_GetClientType_I(ClientIndex)
end;


// WOT/GetClientVersionW
procedure WOT_GetClientVersionW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientVersionW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientVersionW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientVersionW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientVersionW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientVersionW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientVersionW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// WOT/GetClientExeVersionW
procedure WOT_GetClientExeVersionW_I(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientExeVersionW@files:openwg.utils.dll cdecl setuponly';

procedure WOT_GetClientExeVersionW_U(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientExeVersionW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WOT_GetClientExeVersionW(ClientIndex: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        WOT_GetClientExeVersionW_U(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex)
    else
        WOT_GetClientExeVersionW_I(Buffer, {#OPENWGUTILS_BUF_SIZE}, ClientIndex);

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


function CLIENT_GetRecord(Index: Integer): ClientRecord;
begin
  Result.Index := Index;
  Result.Branch := WOT_GetClientBranch(Index);
  Result.LauncherFlavour := WOT_GetClientLauncherFlavour(Index);
  Result.Locale :=  WOT_GetClientLocaleW(Index);
  Result.Path := WOT_GetClientPathW(Index);
  Result.PathMods :=  WOT_GetClientPathModsW(Index);
  Result.PathResmods := WOT_GetClientPathResmodsW(Index);
  Result.Realm :=  WOT_GetClientRealmW(Index);
  Result.ContentType := WOT_GetClientType(Index);
  Result.Version := WOT_GetClientVersionW(Index);
  Result.VersionExe := WOT_GetClientExeVersionW(Index);
end;


function CLIENT_FormatString(Client: ClientRecord): String;
begin
  Result := Client.Version;
  Result := Result + ' [';

  case Client.LauncherFlavour of
     0: Result := Result + ExpandConstant('{cm:openwg_unknown');
     1: Result := Result + 'WG';
     2: Result := Result + '360';
     3: Result := Result + 'Steam';
     4: Result := Result + 'Lesta';
     5: Result := Result + 'Standalone';
  end;

  case Client.Branch of
     0: Result := Result + ExpandConstant('/{cm:openwg_unknown}');
     1: begin
          if Client.LauncherFlavour = 1 then
          begin
            Result := Result + '/' + Client.Realm;
          end;
        end;
     2: Result := Result + ExpandConstant('/{cm:openwg_branch_ct}');
     3: Result := Result + ExpandConstant('/{cm:openwg_branch_st}');
     4: Result := Result + ExpandConstant('/{cm:openwg_branch_sb}');
  end;

  Result := Result + '] - ' + Client.Path;
end;


//
// WoT List
//
var
  wotlist_prev_idx: Integer;

procedure WotList_Update(List: TNewComboBox);
var
  Buffer: String;
  ClientsCount, Index, ListIndex: Integer;
  Str: String;
  Client: ClientRecord;
begin
  SetLength(Buffer, 1024);

  ListIndex := List.ItemIndex;
  ClientsCount := WOT_GetClientsCount();

  List.Items.Clear();

  if ClientsCount > 0 then
  begin
    for Index := 0 to ClientsCount - 1 do
    begin
      Client := CLIENT_GetRecord(Index);
      Str := CLIENT_FormatString(Client);
      List.Items.Add(Str);
    end;
  end;

  List.Items.Add(ExpandConstant('{cm:openwg_browse}'));
  List.ItemIndex := ListIndex;
end;


procedure WotList_AddClient(List: TNewComboBox; ClientPath: String);
var
  Index: Integer;
begin
  // do nothing in case of empty string
  if Length(ClientPath) = 0 then Exit;

  // try to add client
  Index := WOT_AddClientW(ClientPath);
  if Index >= 0 then
  begin
    WotList_Update(List);
    List.ItemIndex := Index;
  end else
  begin
    MsgBox(ExpandConstant('{cm:openwg_client_not_found}'), mbError, MB_OK);
    List.ItemIndex := -1;
  end;

end;


procedure WotList_OnChange(Sender: TObject);
var
  Combobox: TNewComboBox;
begin
  if Sender is TNewComboBox then
  begin
    Combobox := Sender as TNewComboBox;

    if Combobox.Text = ExpandConstant('{cm:openwg_browse}') then
    begin
      // call folder browser
      WizardForm.DirEdit.Text := '';
      WizardForm.DirBrowseButton.OnClick(nil);

      // try to add client
      WotList_AddClient(Combobox, WizardForm.DirEdit.Text);

      // fallback to the previous client in case of failure
      if ((Combobox.ItemIndex < 0) or (Combobox.Text = ExpandConstant('{cm:openwg_browse}'))) and (Combobox.Items.Count > 1) then
        Combobox.ItemIndex := wotlist_prev_idx;
    end
    else
      wotlist_prev_idx := Combobox.ItemIndex;

    WizardForm.DirEdit.Text := WOT_GetClientPathW(Combobox.ItemIndex);
  end;
end;


function WotList_Create(parent: TWinControl; pos_left, pos_top, pos_width, pos_height: Integer):TNewComboBox;
begin;
  Result := TNewComboBox.Create(WizardForm);
  Result.Parent := parent;
  Result.Style := csDropDownList;
  Result.OnChange := @WotList_OnChange;
  Result.SetBounds(pos_left,pos_top,pos_left + pos_width,pos_height);
  WotList_Update(Result);
end;


function WotList_Selected_Record(List: TNewComboBox): ClientRecord;
begin;
  Result := CLIENT_GetRecord(List.ItemIndex);
end;

function WotList_Selected_IsStarted(List: TNewComboBox): Boolean;
begin;
  Result := WOT_ClientIsStarted(List.ItemIndex);
end;

function WotList_Selected_Terminate(List: TNewComboBox): Boolean;
begin;
  Result := WOT_ClientTerminate(List.ItemIndex);
end;

function WotList_Selected_VersionMatch(List: TNewComboBox; VersionPattern: String): Boolean;
begin;
  Result := WOT_ClientIsVersionMatch(List.ItemIndex, VersionPattern);
end;

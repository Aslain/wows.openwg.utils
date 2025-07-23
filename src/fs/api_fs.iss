


//
// FS
//

[Code]

// FS/FileExists
function FS_FileExists_I(Path: String): Integer;
external 'FS_FileExistsW@files:openwg.utils.dll cdecl setuponly';

function FS_FileExists_U(Path: String): Integer;
external 'FS_FileExistsW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_FileExists(Path: String): Integer;
begin
    if IsUninstaller() then
        Result := FS_FileExists_U(Path)
    else
        Result := FS_FileExists_I(Path)
end;


// FS/FileSize
function FS_FileSize_I(Path: String): Integer;
external 'FS_FileSizeW@files:openwg.utils.dll cdecl setuponly';

function FS_FileSize_U(Path: String): Integer;
external 'FS_FileSizeW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_FileSize(Path: String): Integer;
begin
    if IsUninstaller() then
        Result := FS_FileSize_U(Path)
    else
        Result := FS_FileSize_I(Path)
end;


// FS/FileEqual
function FS_FileEqual_I(Path1: String; Path2: String): Integer;
external 'FS_FileEqualW@files:openwg.utils.dll cdecl setuponly';

function FS_FileEqual_U(Path1: String; Path2: String): Integer;
external 'FS_FileEqualW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_FileEqual(Path1: String; Path2: String): Integer;
begin
    if IsUninstaller() then
        Result := FS_FileEqual_U(Path1, Path2)
    else
        Result := FS_FileEqual_I(Path1, Path2)
end;


// FS/Search/Close
function FS_Search_Close_I(Handle: Integer): Boolean;
external 'FS_Search_Close@files:openwg.utils.dll cdecl setuponly';

function FS_Search_Close_U(Handle: Integer): Boolean;
external 'FS_Search_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_Search_Close(Handle: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := FS_Search_Close_U(Handle)
    else
        Result := FS_Search_Close_I(Handle)
end;


// FS/Search/GetCount
function FS_Search_GetCount_I(Handle: Integer): Integer;
external 'FS_Search_GetCount@files:openwg.utils.dll cdecl setuponly';

function FS_Search_GetCount_U(Handle: Integer): Integer;
external 'FS_Search_GetCount@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_Search_GetCount(Handle: Integer): Integer;
begin
    if IsUninstaller() then
        Result := FS_Search_GetCount_U(Handle)
    else
        Result := FS_Search_GetCount_I(Handle)
end;


// FS/Search/GetPath
function FS_Search_GetPathW_I(Handle: Integer; Index: Integer; Output: String; OutputSize: Integer): Integer;
external 'FS_Search_GetPathW@files:openwg.utils.dll cdecl setuponly';

function FS_Search_GetPathW_U(Handle: Integer; Index: Integer; Output: String; OutputSize: Integer): Integer;
external 'FS_Search_GetPathW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_Search_GetPath(Handle: Integer; Index: Integer): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        FS_Search_GetPathW_U(Handle, Index, Buffer, {#OPENWGUTILS_BUF_SIZE})
    else
        FS_Search_GetPathW_I(Handle, Index, Buffer, {#OPENWGUTILS_BUF_SIZE});

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// FS/Search/QueryFolder
function FS_Search_QueryFolderW_I(Regex: String; MaxDepth: Integer): Integer;
external 'FS_Search_QueryFolderW@files:openwg.utils.dll cdecl setuponly';

function FS_Search_QueryFolderW_U(Regex: String; MaxDepth: Integer): Integer;
external 'FS_Search_QueryFolderW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function FS_Search_QueryFolder(Regex: String; MaxDepth: Integer): Integer;
begin
    if IsUninstaller() then
        Result := FS_Search_QueryFolderW_U(Regex, MaxDepth)
    else
        Result := FS_Search_QueryFolderW_I(Regex, MaxDepth)
end;
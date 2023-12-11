


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

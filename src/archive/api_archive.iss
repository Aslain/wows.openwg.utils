

//
// ARCHIVE
//

[Code]

type
    TArchiveFileContext = record
        UncompressedSize: Int64;
        CompressedSize: Int64;
        ModificationTime: Int64;
        Index: Cardinal;
        Crc32: Cardinal;
        Method: Word;
        IsDirectory: Byte;
        IsEncrypted: Byte;
        IsSupported: Byte;
        Reserved: Byte;
    end;

function ARCHIVE_OpenW_I(Path: String): Integer;
external 'ARCHIVE_OpenW@files:openwg.utils.dll cdecl setuponly';

function ARCHIVE_OpenW_U(Path: String): Integer;
external 'ARCHIVE_OpenW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function ARCHIVE_Open(Path: String): Integer;
begin
    if IsUninstaller() then
        Result := ARCHIVE_OpenW_U(Path)
    else
        Result := ARCHIVE_OpenW_I(Path);
end;

function ARCHIVE_Close_I(Handle: Integer): Boolean;
external 'ARCHIVE_Close@files:openwg.utils.dll cdecl setuponly';

function ARCHIVE_Close_U(Handle: Integer): Boolean;
external 'ARCHIVE_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function ARCHIVE_Close(Handle: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := ARCHIVE_Close_U(Handle)
    else
        Result := ARCHIVE_Close_I(Handle);
end;

function ARCHIVE_EntryExistsW_I(Handle: Integer; Entry: String): Boolean;
external 'ARCHIVE_EntryExistsW@files:openwg.utils.dll cdecl setuponly';

function ARCHIVE_EntryExistsW_U(Handle: Integer; Entry: String): Boolean;
external 'ARCHIVE_EntryExistsW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function ARCHIVE_EntryExists(Handle: Integer; Entry: String): Boolean;
begin
    if IsUninstaller() then
        Result := ARCHIVE_EntryExistsW_U(Handle, Entry)
    else
        Result := ARCHIVE_EntryExistsW_I(Handle, Entry);
end;

function ARCHIVE_GetEntryInfoW_I(Handle: Integer; Entry: String; var Context: TArchiveFileContext): Boolean;
external 'ARCHIVE_GetEntryInfoW@files:openwg.utils.dll cdecl setuponly';

function ARCHIVE_GetEntryInfoW_U(Handle: Integer; Entry: String; var Context: TArchiveFileContext): Boolean;
external 'ARCHIVE_GetEntryInfoW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function ARCHIVE_GetEntryInfo(Handle: Integer; Entry: String; var Context: TArchiveFileContext): Boolean;
begin
    if IsUninstaller() then
        Result := ARCHIVE_GetEntryInfoW_U(Handle, Entry, Context)
    else
        Result := ARCHIVE_GetEntryInfoW_I(Handle, Entry, Context);
end;

function ARCHIVE_ExtractToFileW_I(Handle: Integer; Entry: String; Destination: String): Boolean;
external 'ARCHIVE_ExtractToFileW@files:openwg.utils.dll cdecl setuponly';

function ARCHIVE_ExtractToFileW_U(Handle: Integer; Entry: String; Destination: String): Boolean;
external 'ARCHIVE_ExtractToFileW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function ARCHIVE_ExtractToFile(Handle: Integer; Entry: String; Destination: String): Boolean;
begin
    if IsUninstaller() then
        Result := ARCHIVE_ExtractToFileW_U(Handle, Entry, Destination)
    else
        Result := ARCHIVE_ExtractToFileW_I(Handle, Entry, Destination);
end;
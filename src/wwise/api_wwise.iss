


//
// WWISE
//

[Code]

// WWISE/OpenFile
function WWISE_OpenFileW_I(Path: String): Integer;
external 'WWISE_OpenFileW@files:openwg.utils.dll cdecl setuponly';

function WWISE_OpenFileW_U(Path: String): Integer;
external 'WWISE_OpenFileW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WWISE_OpenFile(Path: String): Integer;
begin
    if IsUninstaller() then
        Result := WWISE_OpenFileW_U(Path)
    else
        Result := WWISE_OpenFileW_I(Path)
end;


// WWISE/Close
function WWISE_Close_I(Handle: Integer): Boolean;
external 'WWISE_Close@files:openwg.utils.dll cdecl setuponly';

function WWISE_Close_U(Handle: Integer): Boolean;
external 'WWISE_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WWISE_Close(Handle: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := WWISE_Close_U(Handle)
    else
        Result := WWISE_Close_I(Handle)
end;


// WWISE/LicenseGet
// result: 0 - Unknown, 1 - Unlicensed bank, 2 - Wargaming license
function WWISE_LicenseGet_I(Handle: Integer): Integer;
external 'WWISE_Close@files:openwg.utils.dll cdecl setuponly';

function WWISE_LicenseGet_U(Handle: Integer): Integer;
external 'WWISE_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WWISE_LicenseGet(Handle: Integer): Integer;
begin
    if IsUninstaller() then
        Result := WWISE_LicenseGet_U(Handle)
    else
        Result := WWISE_LicenseGet_I(Handle)
end;


// WWISE/LicenseSet
// license: 1 - unlicensed, 2 - wargaming
function WWISE_LicenseSet_I(Handle: Integer; License: Integer): Boolean;
external 'WWISE_LicenseSet@files:openwg.utils.dll cdecl setuponly';

function WWISE_LicenseSet_U(Handle: Integer; License: Integer): Boolean;
external 'WWISE_LicenseSet@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WWISE_LicenseSet(Handle: Integer; License: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := WWISE_LicenseSet_U(Handle, License)
    else
        Result := WWISE_LicenseSet_I(Handle, License)
end;


// WWISE/SaveFile
// null path - overwrite source file
function WWISE_SaveFileW_I(Handle: Integer; Path: String): Boolean;
external 'WWISE_SaveFileW@files:openwg.utils.dll cdecl setuponly';

function WWISE_SaveFileW_U(Handle: Integer; Path: String): Boolean;
external 'WWISE_SaveFileW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WWISE_SaveFile(Handle: Integer; Path: String): Boolean;
begin
    if IsUninstaller() then
        Result := WWISE_SaveFileW_U(Handle, Path)
    else
        Result := WWISE_SaveFileW_I(Handle, Path)
end;




//
// XML
//

[Code]

// XML/AddKey
function XML_AddKey_I(Handle: Integer; Path: String; Name: String; Value: String): Boolean;
external 'XML_AddKeyW@files:openwg.utils.dll cdecl setuponly';

function XML_AddKey_U(Handle: Integer; Path: String; Name: String; Value: String): Boolean;
external 'XML_AddKeyW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function XML_AddKey(Handle: Integer; Path: String; Name: String; Value: String): Boolean;
begin
    if IsUninstaller() then
        Result := XML_AddKey_U(Handle, Path, Name, Value)
    else
        Result := XML_AddKey_I(Handle, Path, Name, Value)
end;


// XML/Close
function XML_Close_I(Handle: Integer): Boolean;
external 'XML_Close@files:openwg.utils.dll cdecl setuponly';

function XML_Close_U(Handle: Integer): Boolean;
external 'XML_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function XML_Close(Handle: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := XML_Close_U(Handle)
    else
        Result := XML_Close_I(Handle)
end;


// XML/ContainsKey
function XML_ContainsKey_I(Handle: Integer; Path: String): Boolean;
external 'XML_ContainsKeyW@files:openwg.utils.dll cdecl setuponly';

function XML_ContainsKey_U(Handle: Integer; Path: String): Boolean;
external 'XML_ContainsKeyW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function XML_ContainsKey(Handle: Integer; Path: String): Boolean;
begin
    if IsUninstaller() then
        Result := XML_ContainsKey_U(Handle, Path)
    else
        Result := XML_ContainsKey_I(Handle, Path)
end;


// XML/ContainsKeyEx
function XML_ContainsKeyEx_I(Handle: Integer; Path: String; Value: String): Boolean;
external 'XML_ContainsKeyExW@files:openwg.utils.dll cdecl setuponly';

function XML_ContainsKeyEx_U(Handle: Integer; Path: String; Value: String): Boolean;
external 'XML_ContainsKeyExW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function XML_ContainsKeyEx(Handle: Integer; Path: String; Value: String): Boolean;
begin
    if IsUninstaller() then
        Result := XML_ContainsKeyEx_U(Handle, Path, Value)
    else
        Result := XML_ContainsKeyEx_I(Handle, Path, Value)
end;


// XML/OpenFile
function XML_OpenFileW_I(Path: String; AllowCreation: Boolean): Integer;
external 'XML_OpenFileW@files:openwg.utils.dll cdecl setuponly';

function XML_OpenFileW_U(Path: String; AllowCreation: Boolean): Integer;
external 'XML_OpenFileW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function XML_OpenFile(Path: String; AllowCreation: Boolean): Integer;
begin
    if IsUninstaller() then
        Result := XML_OpenFileW_U(Path, AllowCreation)
    else
        Result := XML_OpenFileW_I(Path, AllowCreation)
end;


// XML/SaveFile
function XML_SaveFileW_I(Handle: Integer; Path: String): Boolean;
external 'XML_SaveFileW@files:openwg.utils.dll cdecl setuponly';

function XML_SaveFileW_U(Handle: Integer; Path: String): Boolean;
external 'XML_SaveFileW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function XML_SaveFile(Handle: Integer; Path: String): Boolean;
begin
    if IsUninstaller() then
        Result := XML_SaveFileW_U(Handle, Path)
    else
        Result := XML_SaveFileW_I(Handle, Path)
end;




//
// JSON
//

[Code]

// JSON/OpenFile
function JSON_OpenFileW_I(Path: String; AllowCreation: Boolean): Integer;
external 'JSON_OpenFileW@files:openwg.utils.dll cdecl setuponly';

function JSON_OpenFileW_U(Path: String; AllowCreation: Boolean): Integer;
external 'JSON_OpenFileW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_OpenFile(Path: String; AllowCreation: Boolean): Integer;
begin
    if IsUninstaller() then
        Result := JSON_OpenFileW_U(Path, AllowCreation)
    else
        Result := JSON_OpenFileW_I(Path, AllowCreation)
end;


// JSON/OpenString
function JSON_OpenStringW_I(Text: String): Integer;
external 'JSON_OpenStringW@files:openwg.utils.dll cdecl setuponly';

function JSON_OpenStringW_U(Text: String): Integer;
external 'JSON_OpenStringW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_OpenString(Text: String): Integer;
begin
    if IsUninstaller() then
        Result := JSON_OpenStringW_U(Text)
    else
        Result := JSON_OpenStringW_I(Text)
end;



// Json/Close
function JSON_Close_I(Handle: Integer): Boolean;
external 'JSON_Close@files:openwg.utils.dll cdecl setuponly';

function JSON_Close_U(Handle: Integer): Boolean;
external 'JSON_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_Close(Handle: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := JSON_Close_U(Handle)
    else
        Result := JSON_Close_I(Handle)
end;


// Json/ContainsKey
function JSON_ContainsKeyW_I(Handle: Integer; Path: String): Boolean;
external 'JSON_ContainsKeyW@files:openwg.utils.dll cdecl setuponly';

function JSON_ContainsKeyW_U(Handle: Integer; Path: String): Boolean;
external 'JSON_ContainsKeyW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_ContainsKey(Handle: Integer; Path: String): Boolean;
begin
    if IsUninstaller() then
        Result := JSON_ContainsKeyW_U(Handle, Path)
    else
        Result := JSON_ContainsKeyW_I(Handle, Path)
end;


// Json/GetString
procedure JSON_GetStringW_I(Handle: Integer; Path: String; Output: String; OutputSize: Integer);
external 'JSON_GetStringW@files:openwg.utils.dll cdecl setuponly';

procedure JSON_GetStringW_U(Handle: Integer; Path: String; Output: String; OutputSize: Integer);
external 'JSON_GetStringW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_GetString(Handle: Integer; Path: String): String;
var
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        JSON_GetStringW_U(Handle, Path, Buffer, {#OPENWGUTILS_BUF_SIZE})
    else
        JSON_GetStringW_I(Handle, Path, Buffer, {#OPENWGUTILS_BUF_SIZE});

    Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// Json/SetBool
function JSON_SetBoolW_I(Handle: Integer; Path: String; Value: Boolean): Boolean;
external 'JSON_SetBoolW@files:openwg.utils.dll cdecl setuponly';

function JSON_SetBoolW_U(Handle: Integer; Path: String; Value: Boolean): Boolean;
external 'JSON_SetBoolW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_SetBool(Handle: Integer; Path: String; Value: Boolean): Boolean;
begin
    if IsUninstaller() then
        Result := JSON_SetBoolW_U(Handle, Path, Value)
    else
        Result := JSON_SetBoolW_I(Handle, Path, Value)
end;


// Json/SetDouble
function JSON_SetDoubleW_I(Handle: Integer; Path: String; Value: Double): Boolean;
external 'JSON_SetDoubleW@files:openwg.utils.dll cdecl setuponly';

function JSON_SetDoubleW_U(Handle: Integer; Path: String; Value: Double): Boolean;
external 'JSON_SetDoubleW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_SetDouble(Handle: Integer; Path: String; Value: Double): Boolean;
begin
    if IsUninstaller() then
        Result := JSON_SetDoubleW_U(Handle, Path, Value)
    else
        Result := JSON_SetDoubleW_I(Handle, Path, Value)
end;


// Json/SetInteger
function JSON_SetIntegerW_I(Handle: Integer; Path: String; Value: Integer): Boolean;
external 'JSON_SetIntegerW@files:openwg.utils.dll cdecl setuponly';

function JSON_SetIntegerW_U(Handle: Integer; Path: String; Value: Integer): Boolean;
external 'JSON_SetIntegerW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_SetInteger(Handle: Integer; Path: String; Value: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := JSON_SetIntegerW_U(Handle, Path, Value)
    else
        Result := JSON_SetIntegerW_I(Handle, Path, Value)
end;


// Json/SetString
function JSON_SetStringW_I(Handle: Integer; Path: String; Value: String): Boolean;
external 'JSON_SetStringW@files:openwg.utils.dll cdecl setuponly';

function JSON_SetStringW_U(Handle: Integer; Path: String; Value: String): Boolean;
external 'JSON_SetStringW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function JSON_SetString(Handle: Integer; Path: String; Value: String): Boolean;
begin
    if IsUninstaller() then
        Result := JSON_SetStringW_U(Handle, Path, Value)
    else
        Result := JSON_SetStringW_I(Handle, Path, Value)
end;

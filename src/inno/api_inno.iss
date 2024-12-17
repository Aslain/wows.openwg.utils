


//
// PROCESS
//

[Code]

// INNO/ComponentEntryGetName
function INNO_ComponentEntryGetNameW_I(Object: TObject; Buffer: String; BufferSize: Integer): Boolean;
external 'INNO_ComponentEntryGetNameW@files:openwg.utils.dll cdecl setuponly';

function INNO_ComponentEntryGetNameW_U(Object: TObject; Buffer: String; BufferSize: Integer): Boolean;
external 'INNO_ComponentEntryGetNameW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function INNO_ComponentEntryGetName(Object: TObject): String;
var
    FunctionResult: Boolean;
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        FunctionResult := INNO_ComponentEntryGetNameW_U(Object, Buffer, {#OPENWGUTILS_BUF_SIZE})
    else
        FunctionResult := INNO_ComponentEntryGetNameW_I(Object, Buffer, {#OPENWGUTILS_BUF_SIZE});

    if FunctionResult then
        Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// INNO/ComponentEntryGetDescription
function INNO_ComponentEntryGetDescriptionW_I(Object: TObject; Buffer: String; BufferSize: Integer): Boolean;
external 'INNO_ComponentEntryGetDescriptionW@files:openwg.utils.dll cdecl setuponly';

function INNO_ComponentEntryGetDescriptionW_U(Object: TObject; Buffer: String; BufferSize: Integer): Boolean;
external 'INNO_ComponentEntryGetDescriptionW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function INNO_ComponentEntryGetDescription(Object: TObject): String;
var
    FunctionResult: Boolean;
    Buffer: String;
begin
    SetLength(Buffer, {#OPENWGUTILS_BUF_SIZE});

    if IsUninstaller() then
        FunctionResult := INNO_ComponentEntryGetDescriptionW_U(Object, Buffer, {#OPENWGUTILS_BUF_SIZE})
    else
        FunctionResult := INNO_ComponentEntryGetDescriptionW_I(Object, Buffer, {#OPENWGUTILS_BUF_SIZE});

    if FunctionResult then
        Result := Copy(Buffer, 1, Pos(#0, Buffer)-1);
end;


// INNO/ChecklistGetItemName
function INNO_ChecklistGetItemName(Checklist: TNewCheckListBox; Index: Integer): String;
begin
    Result := INNO_ComponentEntryGetName(Checklist.ItemObject[Index]);
end;

// INNO/ChecklistGetItemDescription
function INNO_ChecklistGetItemDescription(Checklist: TNewCheckListBox; Index: Integer): String;
begin
    Result := INNO_ComponentEntryGetDescription(Checklist.ItemObject[Index]);
end;

// INNO/ChecklistGetItemIndex
function INNO_ChecklistGetItemIndex(Checklist: TNewCheckListBox; Name: String): Integer;
var
    Index: Integer;
begin
    Result := -1;

    for Index := 0 to Checklist.Items.Count - 1 do
    begin
        if CompareStr(INNO_ChecklistGetItemName(Checklist, Index), Name) = 0 then
        begin
            Result := Index;
            Exit;
        end;
    end;
end;

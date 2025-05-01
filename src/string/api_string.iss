


//
// STRING
//

[Code]

// STRING/MatchRegex
function STRING_MatchRegex_I(Input: String; Search: String): Boolean;
external 'STRING_MatchRegex@files:openwg.utils.dll cdecl setuponly';

function STRING_MatchRegex_U(Input: String; Search: String): Boolean;
external 'STRING_MatchRegex@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function STRING_MatchRegex(Input: String; Search: String): Boolean;
begin
    if IsUninstaller() then
        Result := STRING_MatchRegex_U(Input, Search)
    else
        Result := STRING_MatchRegex_I(Input, Search);
end;



// STRING/ReplaceRegex
function STRING_ReplaceRegex_I(Input: String; Search: String; Replace: String; Output: String; BufferSize: Integer): Integer;
external 'STRING_ReplaceRegex@files:openwg.utils.dll cdecl setuponly';

function STRING_ReplaceRegex_U(Input: String; Search: String; Replace: String; Output: String; BufferSize: Integer): Integer;
external 'STRING_ReplaceRegex@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function STRING_ReplaceRegex(Input: String; Search: String; Replace: String): String;
var
    ResultSize: Integer;
    ErrorCode: Integer;
begin
    ResultSize := Length(Input)*2;
    SetLength(Result, ResultSize);

    if IsUninstaller() then
        ErrorCode := STRING_ReplaceRegex_U(Input, Search, Replace, Result, ResultSize)
    else
        ErrorCode := STRING_ReplaceRegex_I(Input, Search, Replace, Result, ResultSize);

    // not enough space
    if (ErrorCode < 0) then
    begin
        ResultSize := -ErrorCode;
        SetLength(Result, ResultSize);
        if IsUninstaller() then
            ErrorCode := STRING_ReplaceRegex_U(Input, Search, Replace, Result, ResultSize)
        else
            ErrorCode := STRING_ReplaceRegex_I(Input, Search, Replace, Result, ResultSize);
    end;

    // general error
    if (ErrorCode = 0) then
    begin
        Result := Input;
        Exit;
    end;

    // crop result
    Result := Copy(Result, 1, Pos(#0, Result)-1);
end;


function STRING_Split(const Value: string; Delimiter: Char): TStringList;
var
    S: string;
begin
    S := Value;
    StringChangeEx(S, Delimiter, #13#10, True);
    Result := TStringList.Create()
    Result.Text := S;
end;





//
// STRING
//

[Code]

// String/LoadFromFile
function STRING_LoadFromFile_I(FilePath: String; Buffer: String; BufferSize: Integer): Integer;
external 'STRING_LoadFromFile@files:openwg.utils.dll cdecl setuponly';

function STRING_LoadFromFile_U(FilePath: String; Buffer: String; BufferSize: Integer): Integer;
external 'STRING_LoadFromFile_U@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function STRING_LoadFromFile(FilePath: String): String;
var
    ResultSize: Integer;
    ErrorCode: Integer;
begin
    ResultSize := FS_FileSize(FilePath);
    if ResultSize = 0 then
        Exit;
    ResultSize := ResultSize * 2;
    SetLength(Result, ResultSize);

    if IsUninstaller() then
        ErrorCode := STRING_LoadFromFile_U(FilePath, Result, ResultSize)
    else
        ErrorCode := STRING_LoadFromFile_I(FilePath, Result, ResultSize);

    // not enough space
    if (ErrorCode < 0) then
        begin
            ResultSize := -ErrorCode;
            SetLength(Result, ResultSize);
            if IsUninstaller() then
                ErrorCode := STRING_LoadFromFile_U(FilePath, Result, ResultSize)
            else
                ErrorCode := STRING_LoadFromFile_I(FilePath, Result, ResultSize);
        end;

    // general error
    if (ErrorCode = 0) then
        Exit;

    // crop result
    Result := Copy(Result, 1, Pos(#0, Result)-1);
end;


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


// STRING/ReplaceRegexEx
function STRING_ReplaceRegexEx_I(Input: String; Search: String; Replace: String; Output: String; BufferSize: Integer; FirstOnly: Boolean): Integer;
external 'STRING_ReplaceRegexEx@files:openwg.utils.dll cdecl setuponly';

function STRING_ReplaceRegexEx_U(Input: String; Search: String; Replace: String; Output: String; BufferSize: Integer; FirstOnly: Boolean): Integer;
external 'STRING_ReplaceRegexEx@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function STRING_ReplaceRegexEx(Input: String; Search: String; Replace: String; FirstOnly: Boolean): String;
var
    ResultSize: Integer;
    ErrorCode: Integer;
begin
    ResultSize := Length(Input)*2;
    SetLength(Result, ResultSize);

    if IsUninstaller() then
        ErrorCode := STRING_ReplaceRegexEx_U(Input, Search, Replace, Result, ResultSize, FirstOnly)
    else
        ErrorCode := STRING_ReplaceRegexEx_I(Input, Search, Replace, Result, ResultSize, FirstOnly);

    // not enough space
    if (ErrorCode < 0) then
    begin
        ResultSize := -ErrorCode;
        SetLength(Result, ResultSize);
        if IsUninstaller() then
            ErrorCode := STRING_ReplaceRegexEx_U(Input, Search, Replace, Result, ResultSize, FirstOnly)
        else
            ErrorCode := STRING_ReplaceRegexEx_I(Input, Search, Replace, Result, ResultSize, FirstOnly);
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


// STRING/ReplaceRegex
function STRING_ReplaceRegex(Input: String; Search: String; Replace: String): String;
begin
    Result := STRING_ReplaceRegexEx(Input, Search, Replace, False);
end;


// String/Split
function STRING_Split(const Value: string; Delimiter: Char): TStringList;
var
    S: string;
begin
    S := Value;
    StringChangeEx(S, Delimiter, #13#10, True);
    Result := TStringList.Create()
    Result.Text := S;
end;


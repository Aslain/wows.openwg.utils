


//
// STRING
//

[Code]

// String/LoadFromFile
function STRING_LoadFromFile_I(FilePath: String; Buffer: String; BufferSize: Integer): Integer;
external 'STRING_LoadFromFile@files:openwg.utils.dll cdecl setuponly';

function STRING_LoadFromFile_U(FilePath: String; Buffer: String; BufferSize: Integer): Integer;
external 'STRING_LoadFromFile@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function STRING_LoadFromFile(FilePath: String): String;
var
    BufferBytes: Integer;
    BufferChars: Integer;
    ErrorCode: Integer;
begin
    Result := '';

    BufferBytes := FS_FileSize(FilePath);
    if BufferBytes <= 0 then
        Exit;

    // UTF-8 -> UTF-16 worst-case expansion + UTF-16 null terminator
    BufferBytes := BufferBytes * 2 + 2;
    BufferChars := (BufferBytes + 1) div 2;
    SetLength(Result, BufferChars);

    if IsUninstaller() then
        ErrorCode := STRING_LoadFromFile_U(FilePath, Result, BufferChars * 2)
    else
        ErrorCode := STRING_LoadFromFile_I(FilePath, Result, BufferChars * 2);

    // Fatal Error
    if (ErrorCode = -2147483648) then
        Exit;

    // not enough space
    if (ErrorCode < 0) then
        begin
            BufferBytes := -ErrorCode;
            BufferChars := (BufferBytes + 1) div 2;
            SetLength(Result, BufferChars);
            if IsUninstaller() then
                ErrorCode := STRING_LoadFromFile_U(FilePath, Result, BufferChars * 2)
            else
                ErrorCode := STRING_LoadFromFile_I(FilePath, Result, BufferChars * 2);
        end;

    // Fatal Error / unresolved allocation error
    if (ErrorCode = -2147483648) or (ErrorCode < 0) then
        Exit;

    // empty string
    if (ErrorCode = 0) then
        Exit;

    // ErrorCode = UTF-16 text length in bytes (without null terminator)
    SetLength(Result, ErrorCode div 2);
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
    BufferChars: Integer;
    BufferBytes: Integer;
    ErrorCode: Integer;
begin
    BufferChars := Length(Input) + 1;
    if (BufferChars < 1) then
        BufferChars := 1;

    SetLength(Result, BufferChars);
    BufferBytes := BufferChars * 2;

    if IsUninstaller() then
        ErrorCode := STRING_ReplaceRegexEx_U(Input, Search, Replace, Result, BufferBytes, FirstOnly)
    else
        ErrorCode := STRING_ReplaceRegexEx_I(Input, Search, Replace, Result, BufferBytes, FirstOnly);

    // not enough space
    if (ErrorCode < 0) then
    begin
        BufferBytes := -ErrorCode;
        BufferChars := (BufferBytes + 1) div 2;
        SetLength(Result, BufferChars);

        if IsUninstaller() then
            ErrorCode := STRING_ReplaceRegexEx_U(Input, Search, Replace, Result, BufferChars * 2, FirstOnly)
        else
            ErrorCode := STRING_ReplaceRegexEx_I(Input, Search, Replace, Result, BufferChars * 2, FirstOnly);
    end;

    // general error
    if (ErrorCode = 0) then
    begin
        Result := Input;
        Exit;
    end;

    // ErrorCode = output length in bytes including UTF-16 null terminator
    if (ErrorCode >= 2) then
        SetLength(Result, (ErrorCode div 2) - 1)
    else
        Result := '';
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


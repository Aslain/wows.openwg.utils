[Files]
Source: "../../src/string/test_assets/string_load_from_file_1_utf8.txt"; Flags: dontcopy noencryption
Source: "../../src/string/test_assets/string_load_from_file_1_utf8bom.txt"; Flags: dontcopy noencryption
Source: "../../src/string/test_assets/string_load_from_file_1_utf16le.txt"; Flags: dontcopy noencryption

Source: "../../src/string/test_assets/string_replace_regex_1_before.txt"; Flags: dontcopy noencryption
Source: "../../src/string/test_assets/string_replace_regex_1_after.txt"; Flags: dontcopy noencryption

[Code]

//
// TEST/STRING/LoadFromFile/1
//

function TEST_STRING_LoadFromFile_1_utf8(): Boolean;
var
    Text: String;
begin
    Result := False;

    ExtractTemporaryFile('string_load_from_file_1_utf8.txt');
    Text := STRING_LoadFromFile(ExpandConstant('{tmp}/string_load_from_file_1_utf8.txt'));
    if length(Text) = 80 then
        Result := True;
end;


function TEST_STRING_LoadFromFile_1_utf8bom(): Boolean;
var
    Text: String;
begin
    Result := False;

    ExtractTemporaryFile('string_load_from_file_1_utf8bom.txt');
    Text := STRING_LoadFromFile(ExpandConstant('{tmp}/string_load_from_file_1_utf8bom.txt'));
    if Length(Text) = 80 then
        Result := True;
end;


function TEST_STRING_LoadFromFile_1_utf16le(): Boolean;
var
    Text: String;
begin
    Result := False;

    ExtractTemporaryFile('string_load_from_file_1_utf16le.txt');
    Text := STRING_LoadFromFile(ExpandConstant('{tmp}/string_load_from_file_1_utf16le.txt'));
    if Length(Text) = 79 then
        Result := True;
end;



//
// TEST/STRING/ReplaceRegex/1
//

function TEST_STRING_ReplaceRegex_1(): Boolean;
var
    TextBefore: String;
    TextAfter: String;
    TextAfterExpected: String;
begin
    Result := False;

    ExtractTemporaryFile('string_replace_regex_1_before.txt');
    TextBefore := STRING_LoadFromFile(ExpandConstant('{tmp}/string_replace_regex_1_before.txt'));
    if length(TextBefore) <> 80 then
        Exit;

    ExtractTemporaryFile('string_replace_regex_1_after.txt');
    TextAfterExpected := STRING_LoadFromFile(ExpandConstant('{tmp}/string_replace_regex_1_after.txt'));
    if length(TextAfterExpected) <> 177 then
        Exit;

    TextAfter := STRING_ReplaceRegex(TextBefore, '(<loadBanks>)', '$1<bank><name>extended_sounds.bnk</name></bank><bank><name>hangar_h04_remday_2015.bnk</name></bank>');
    if length(TextAfter) <> 177 then
        Exit;

    if CompareText(TextAfter, TextAfterExpected) <> 0 then
        Exit;

    Result := True;
end;



//
// TEST/STRING
//

procedure TEST_STRING_Run();
begin
    TEST_SetResult('/string/load_from_file/1/utf8', TEST_STRING_LoadFromFile_1_utf8());
    TEST_SetResult('/string/load_from_file/1/utf8bom', TEST_STRING_LoadFromFile_1_utf8bom());
    TEST_SetResult('/string/load_from_file/1/utf16le', TEST_STRING_LoadFromFile_1_utf16le());
      
    TEST_SetResult('/string/replace_regex/1', TEST_STRING_ReplaceRegex_1());
end;

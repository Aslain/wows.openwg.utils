[Code]

var
    g_test_json: Integer;

procedure TEST_SetResult(TestName: String; Value: Boolean);
begin
    JSON_SetBool(g_test_json, TestName, Value);
end;


procedure TEST_Start();
begin
    g_test_json := JSON_OpenFile(ExpandConstant('{src}/test_result.json'), True);
end;


procedure TEST_Finish();
begin
    JSON_Close(g_test_json);
end;

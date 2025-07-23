[Code]

procedure TEST_Run();
begin
    TEST_Start();
    TEST_STRING_Run();
    TEST_Finish();
end;

function InitializeSetup: Boolean;
begin
  TEST_Run();
  Result := False;
end;
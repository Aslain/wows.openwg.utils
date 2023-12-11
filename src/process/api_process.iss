


//
// PROCESS
//

[Code]

// PROCESS/GetRunningInDirectoryW
function PROCESS_GetRunningInDirectoryW_I(DirectoryPth: String; Buffer: String; BufferSize: Integer): Integer;
external 'PROCESS_GetRunningInDirectoryW@files:openwg.utils.dll cdecl setuponly';

function PROCESS_GetRunningInDirectoryW_U(DirectoryPth: String; Buffer: String; BufferSize: Integer): Integer;
external 'PROCESS_GetRunningInDirectoryW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function PROCESS_GetRunningInDirectoryW(DirectoryPth: String; Buffer: String; BufferSize: Integer): Integer;
begin
    if IsUninstaller() then
        Result := PROCESS_GetRunningInDirectoryW_U(DirectoryPth, Buffer, BufferSize)
    else
        Result := PROCESS_GetRunningInDirectoryW_I(DirectoryPth, Buffer, BufferSize)
end;


//PROCESS/TerminateProcess
function PROCESS_TerminateProcess_I(ProcessPath: String): Boolean;
external 'PROCESS_TerminateProcess@files:openwg.utils.dll cdecl setuponly';

function PROCESS_TerminateProcess_U(ProcessPath: String): Boolean;
external 'PROCESS_TerminateProcess@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function PROCESS_TerminateProcess(ProcessPath: String): Boolean;
begin
    if IsUninstaller() then
        Result := PROCESS_TerminateProcess_U(ProcessPath)
    else
        Result := PROCESS_TerminateProcess_I(ProcessPath)
end;


function PROCESS_GetRunningProcesses(szPath: string): TStringList;
var
    Buffer: String;
    ProcCount: Integer;
begin
    SetLength(Buffer, 1024);
    ProcCount:=PROCESS_GetRunningInDirectoryW(szPath, Buffer, 1024);
    if ProcCount > 0 then
    begin
        Buffer:=Copy(Buffer, 1, Pos(#0, Buffer)-1);
        Result:=STRING_Split(Buffer,';');
        Exit;
    end;
    Result:=TStringList.Create();
end;
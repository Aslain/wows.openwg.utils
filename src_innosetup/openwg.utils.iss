#ifndef XVMEXTENSION_DIR
#define XVMEXTENSION_DIR SourcePath
#endif

[Files]
Source: "{#XVMEXTENSION_DIR}\openwg.utils.x86_32.dll"; DestName: openwg.utils.dll; Flags: dontcopy;


[Code]

//BWXML
//zero on success, negative value on error
function BWXML_UnpackW(PathPacked: String; PathUnpacked: String): Integer;
external 'BWXML_UnpackW@files:openwg.utils.dll cdecl';


//JSON
function JSON_ContainsKeyW(JSON: String; Path: String): Boolean;
external 'JSON_ContainsKeyW@files:openwg.utils.dll cdecl';

procedure JSON_GetValueW(JSON: String; Path: String; Buffer: String; BufferSize: Integer);
external 'JSON_GetValueW@files:openwg.utils.dll cdecl';

procedure JSON_SetValueBoolW(FileFullName: String; ValuePath: String; Value: Boolean);
external 'JSON_SetValueBoolW@files:openwg.utils.dll cdecl';

//value isAdd - True add value to the array, False replace the whole array
procedure JSON_SetValueObjW(FileFullName: String; Value: String; isAdd: Boolean);
external 'JSON_SetValueObjW@files:openwg.utils.dll cdecl';

procedure JSON_GetNamesAndValuesW(FileFullName: String; Path: String; BufNames: String; BufValues: String; BufferSize: Integer);
external 'JSON_GetNamesAndValuesW@files:openwg.utils.dll cdecl';

procedure JSON_GetNamesAndValuesW_S(StrJSON: String; BufNames: String; BufValues: String; BufferSize: Integer);
external 'JSON_GetNamesAndValuesW_S@files:openwg.utils.dll cdecl';

procedure JSON_GetArrayValueW_S(StrJSON: String; BufValues: String; BufferSize: Integer);
external 'JSON_GetArrayValueW_S@files:openwg.utils.dll cdecl';

procedure IMAGEDRAW_PngToBmp(FileName: String);
external 'IMAGEDRAW_PngToBmp@files:openwg.utils.dll cdecl';


//PROCESS
function PROCESS_GetRunningInDirectoryW(DirectoryPth: String; Buffer: String; BufferSize: Integer): Boolean;
external 'PROCESS_GetRunningInDirectoryW@files:openwg.utils.dll cdecl';

function PROCESS_TerminateProcess(ProcessName: String): Boolean;
external 'PROCESS_TerminateProcess@files:openwg.utils.dll cdecl';


//SPLASHSCREEN
function SPLASHSCREEN_ShowSplashScreenW(FileName: String; SecondsToShow: Integer): Boolean;
external 'SPLASHSCREEN_ShowSplashScreenW@files:openwg.utils.dll cdecl';

//Wine
function WINE_IsRunningUnder(): Boolean;
external 'WINE_IsRunningUnder@files:openwg.utils.dll cdecl';


//WoT
function WOT_AddClientW(ClientPath: String): Integer;
external 'WOT_AddClientW@files:openwg.utils.dll cdecl';

procedure WOT_GetPreferredClientPathW(Buffer: String; BufferSize: Integer);
external 'WOT_GetPreferredClientPathW@files:openwg.utils.dll cdecl';

function WOT_GetClientsCount(): Integer;
external 'WOT_GetClientsCount@files:openwg.utils.dll cdecl';

function WOT_GetClientBranch(ClientIndex: Integer): Integer;
external 'WOT_GetClientBranch@files:openwg.utils.dll cdecl';

function WOT_GetClientType(ClientIndex: Integer): Integer;
external 'WOT_GetClientType@files:openwg.utils.dll cdecl';

function WOT_GetClientWgcFlavour(ClientIndex: Integer): Integer;
external 'WOT_GetClientWgcFlavour@files:openwg.utils.dll cdecl';

procedure WOT_GetClientLocaleW(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientLocaleW@files:openwg.utils.dll cdecl';

procedure WOT_GetClientPathW(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientPathW@files:openwg.utils.dll cdecl';

procedure WOT_GetClientVersionW(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientVersionW@files:openwg.utils.dll cdecl';

procedure WOT_GetClientExeVersionW(Buffer: String; BufferSize: Integer; ClientIndex: Integer);
external 'WOT_GetClientExeVersionW@files:openwg.utils.dll cdecl';

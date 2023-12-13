


//
// SPLASHSCREEN
//

[Code]

//SPLASHSCREEN/ShowSplashScreenW
function SPLASHSCREEN_ShowSplashScreenW_I(FileName: String; SecondsToShow: Integer): Integer;
external 'SPLASHSCREEN_ShowSplashScreenW@files:openwg.utils.dll cdecl setuponly';

function SPLASHSCREEN_ShowSplashScreenW_U(FileName: String; SecondsToShow: Integer): Integer;
external 'SPLASHSCREEN_ShowSplashScreenW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function SPLASHSCREEN_ShowSplashScreenW(FileName: String; SecondsToShow: Integer): Integer;
begin
    if IsUninstaller() then
        Result := SPLASHSCREEN_ShowSplashScreenW_U(FileName, SecondsToShow)
    else
        Result := SPLASHSCREEN_ShowSplashScreenW_I(FileName, SecondsToShow)
end;


// SPLASHSCREEN/Close
function SPLASHSCREEN_Close_I(Handle: Integer): Boolean;
external 'SPLASHSCREEN_Close@files:openwg.utils.dll cdecl setuponly';

function SPLASHSCREEN_Close_U(Handle: Integer): Boolean;
external 'SPLASHSCREEN_Close@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function SPLASHSCREEN_Close(Handle: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := SPLASHSCREEN_Close_U(Handle)
    else
        Result := SPLASHSCREEN_Close_I(Handle)
end;


//SPLASHSCREEN/Show
function SPLASHSCREEN_ShowW_I(FileName: String): Integer;
external 'SPLASHSCREEN_ShowW@files:openwg.utils.dll cdecl setuponly';

function SPLASHSCREEN_ShowW_U(FileName: String): Integer;
external 'SPLASHSCREEN_ShowW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function SPLASHSCREEN_Show(FileName: String): Integer;
begin
    if IsUninstaller() then
        Result := SPLASHSCREEN_ShowW_U(FileName)
    else
        Result := SPLASHSCREEN_ShowW_I(FileName)
end;



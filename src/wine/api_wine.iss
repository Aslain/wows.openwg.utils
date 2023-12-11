


//
// WOT
//

[Code]

// WINE/IsRunningUnder
function WINE_IsRunningUnder_I(): Boolean;
external 'WINE_IsRunningUnder@files:openwg.utils.dll cdecl setuponly';

function WINE_IsRunningUnder_U(): Boolean;
external 'WINE_IsRunningUnder@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function WINE_IsRunningUnder(): Boolean;
begin
    if IsUninstaller() then
        Result := WINE_IsRunningUnder_U()
    else
        Result := WINE_IsRunningUnder_I()
end;

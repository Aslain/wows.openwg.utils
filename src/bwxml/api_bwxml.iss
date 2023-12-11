


//
// BWXML
//

[Code]

// BWXML/UnpackW
function BWXML_UnpackW_I(PathPacked: String; PathUnpacked: String): Integer;
external 'BWXML_UnpackW@files:openwg.utils.dll cdecl setuponly';

function BWXML_UnpackW_U(PathPacked: String; PathUnpacked: String): Integer;
external 'BWXML_UnpackW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function BWXML_UnpackW(PathPacked: String; PathUnpacked: String): Integer;
begin
    if IsUninstaller() then
        Result := BWXML_UnpackW_U(PathPacked, PathUnpacked)
    else
        Result := BWXML_UnpackW_I(PathPacked, PathUnpacked)
end;
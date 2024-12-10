


//
// IMAGEDRAW
//

[Code]

// IMAGEDRAW/PngToBmp
procedure IMAGEDRAW_PngToBmp_I(FileName: String);
external 'IMAGEDRAW_PngToBmp@files:openwg.utils.dll cdecl setuponly';

procedure IMAGEDRAW_PngToBmp_U(FileName: String);
external 'IMAGEDRAW_PngToBmp@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

procedure IMAGEDRAW_PngToBmp(FileName: String);
begin
    if IsUninstaller() then
        IMAGEDRAW_PngToBmp_U(FileName)
    else
        IMAGEDRAW_PngToBmp_I(FileName)
end;




//
// IMAGE
//

[Code]

// IMAGE/BitmapAlphaPremultiply
function IMAGE_BitmapAlphaPremultiply_I(Bitmap: Integer): Boolean;
external 'IMAGE_BitmapAlphaPremultiply@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapAlphaPremultiply_U(Bitmap: Integer): Boolean;
external 'IMAGE_BitmapAlphaPremultiply@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapAlphaPremultiply(Bitmap: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapAlphaPremultiply_U(Bitmap)
    else
        Result := IMAGE_BitmapAlphaPremultiply_I(Bitmap)
end;



// IMAGE/BitmapBlend
function IMAGE_BitmapBlend_I(Bitmap1: Integer; Bitmap2: Integer): Integer;
external 'IMAGE_BitmapBlend@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapBlend_U(Bitmap1: Integer; Bitmap2: Integer): Integer;
external 'IMAGE_BitmapBlend@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapBlend(Bitmap1: Integer; Bitmap2: Integer): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapBlend_U(Bitmap1, Bitmap2)
    else
        Result := IMAGE_BitmapBlend_I(Bitmap1, Bitmap2)
end;



// IMAGE/BitmapFree
function IMAGE_BitmapFree_I(Bitmap: Integer): Boolean;
external 'IMAGE_BitmapFree@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapFree_U(Bitmap: Integer): Boolean;
external 'IMAGE_BitmapFree@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapFree(Bitmap: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapFree_U(Bitmap)
    else
        Result := IMAGE_BitmapFree_I(Bitmap)
end;



// IMAGE/BitmapGetHeight
function IMAGE_BitmapGetHeight_I(Bitmap: Integer): Integer;
external 'IMAGE_BitmapGetHeight@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapGetHeight_U(Bitmap: Integer): Integer;
external 'IMAGE_BitmapGetHeight@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapGetHeight(Bitmap: Integer): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapGetHeight_U(Bitmap)
    else
        Result := IMAGE_BitmapGetHeight_I(Bitmap)
end;



// IMAGE/BitmapGetWidth
function IMAGE_BitmapGetWidth_I(Bitmap: Integer): Integer;
external 'IMAGE_BitmapGetWidth@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapGetWidth_U(Bitmap: Integer): Integer;
external 'IMAGE_BitmapGetWidth@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapGetWidth(Bitmap: Integer): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapGetWidth_U(Bitmap)
    else
        Result := IMAGE_BitmapGetWidth_I(Bitmap)
end;



// IMAGE/BitmapLoad
function IMAGE_BitmapLoadW_I(Filename: String): Integer;
external 'IMAGE_BitmapLoadW@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapLoadW_U(Filename: String): Integer;
external 'IMAGE_BitmapLoadW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapLoad(Filename: String): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapLoadW_U(Filename)
    else
        Result := IMAGE_BitmapLoadW_I(Filename)
end;



// IMAGE/BrushCreate
function IMAGE_BrushCreate_I(Bitmap: Integer): Integer;
external 'IMAGE_BrushCreate@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BrushCreate_U(Bitmap: Integer): Integer;
external 'IMAGE_BrushCreate@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BrushCreate(Bitmap: Integer): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BrushCreate_U(Bitmap)
    else
        Result := IMAGE_BrushCreate_I(Bitmap)
end;



// IMAGE/BrushFree
function IMAGE_BrushFree_I(Brush: Integer): Boolean;
external 'IMAGE_BrushFree@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BrushFree_U(Brush: Integer): Boolean;
external 'IMAGE_BrushFree@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BrushFree(Brush: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := IMAGE_BrushFree_U(Brush)
    else
        Result := IMAGE_BrushFree_I(Brush)
end;

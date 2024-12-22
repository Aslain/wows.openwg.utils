


//
// IMAGE
//

[Code]

// IMAGE/BitmapAlphaPremultiply
function IMAGE_BitmapAlphaPremultiply_I(Bitmap: HBITMAP): Boolean;
external 'IMAGE_BitmapAlphaPremultiply@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapAlphaPremultiply_U(Bitmap: HBITMAP): Boolean;
external 'IMAGE_BitmapAlphaPremultiply@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapAlphaPremultiply(Bitmap: HBITMAP): Boolean;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapAlphaPremultiply_U(Bitmap)
    else
        Result := IMAGE_BitmapAlphaPremultiply_I(Bitmap)
end;



// IMAGE/BitmapBlend
function IMAGE_BitmapBlend_I(Bitmap1: HBITMAP; Bitmap2: HBITMAP; DstX: Integer; DstY: Integer): Boolean;
external 'IMAGE_BitmapBlend@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapBlend_U(Bitmap1: HBITMAP; Bitmap2: HBITMAP; DstX: Integer; DstY: Integer): Boolean;
external 'IMAGE_BitmapBlend@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapBlend(Bitmap1: HBITMAP; Bitmap2: HBITMAP; DstX: Integer; DstY: Integer): Boolean;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapBlend_U(Bitmap1, Bitmap2, DstX, DstY)
    else
        Result := IMAGE_BitmapBlend_I(Bitmap1, Bitmap2, DstX, DstY)
end;


// IMAGE/BitmapClone
function IMAGE_BitmapClone_I(Bitmap: HBITMAP): HBITMAP;
external 'IMAGE_BitmapClone@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapClone_U(Bitmap: HBITMAP): HBITMAP;
external 'IMAGE_BitmapClone@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapClone(Bitmap: HBITMAP): HBITMAP;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapClone_U(Bitmap)
    else
        Result := IMAGE_BitmapClone_I(Bitmap)
end;


// IMAGE/BitmapFree
function IMAGE_BitmapFree_I(Bitmap: HBITMAP): Boolean;
external 'IMAGE_BitmapFree@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapFree_U(Bitmap: HBITMAP): Boolean;
external 'IMAGE_BitmapFree@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapFree(Bitmap: HBITMAP): Boolean;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapFree_U(Bitmap)
    else
        Result := IMAGE_BitmapFree_I(Bitmap)
end;



// IMAGE/BitmapGetHeight
function IMAGE_BitmapGetHeight_I(Bitmap: HBITMAP): Integer;
external 'IMAGE_BitmapGetHeight@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapGetHeight_U(Bitmap: HBITMAP): Integer;
external 'IMAGE_BitmapGetHeight@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapGetHeight(Bitmap: HBITMAP): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapGetHeight_U(Bitmap)
    else
        Result := IMAGE_BitmapGetHeight_I(Bitmap)
end;



// IMAGE/BitmapGetWidth
function IMAGE_BitmapGetWidth_I(Bitmap: HBITMAP): Integer;
external 'IMAGE_BitmapGetWidth@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapGetWidth_U(Bitmap: HBITMAP): Integer;
external 'IMAGE_BitmapGetWidth@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapGetWidth(Bitmap: HBITMAP): Integer;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapGetWidth_U(Bitmap)
    else
        Result := IMAGE_BitmapGetWidth_I(Bitmap)
end;



// IMAGE/BitmapLoad
function IMAGE_BitmapLoadW_I(Filename: String): HBITMAP;
external 'IMAGE_BitmapLoadW@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapLoadW_U(Filename: String): HBITMAP;
external 'IMAGE_BitmapLoadW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapLoad(Filename: String): HBITMAP;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapLoadW_U(Filename)
    else
        Result := IMAGE_BitmapLoadW_I(Filename)
end;



// IMAGE/BitmapResize
function IMAGE_BitmapResize_I(Bitmap: HBITMAP; Width: Integer; Height: Integer): Integer;
external 'IMAGE_BitmapResize@files:openwg.utils.dll cdecl setuponly';

function IMAGE_BitmapResize_U(Bitmap: HBITMAP; Width: Integer; Height: Integer): HBITMAP;
external 'IMAGE_BitmapResize@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function IMAGE_BitmapResize(Bitmap: HBITMAP; Width: Integer; Height: Integer): HBITMAP;
begin
    if IsUninstaller() then
        Result := IMAGE_BitmapResize_U(Bitmap, Width, Height)
    else
        Result := IMAGE_BitmapResize_I(Bitmap, Width, Height)
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



// IMAGE/TBitmapLoad
function IMAGE_TBitmapLoad(Filename: String; Scale: Boolean; PremultiplyAlpha: Boolean): TBitmap;
var
    Handle: HBITMAP;
    HandleTemp: HBITMAP;
begin
    Handle := IMAGE_BitmapLoad(Filename);
    if Handle = 0 then
        Exit;

    if Scale then
    begin
        HandleTemp := IMAGE_BitmapResize(Handle, ScaleX(IMAGE_BitmapGetWidth(Handle)), ScaleX(IMAGE_BitmapGetHeight(Handle)));
        IMAGE_BitmapFree(Handle);
        if HandleTemp = 0 then
            Exit;
        Handle := HandleTemp;
    end;

    if PremultiplyAlpha then
        IMAGE_BitmapAlphaPremultiply(Handle);

    Result := TBitmap.Create();
    Result.Handle := Handle;
end;



// IMAGE/IMAGE_TBitmapLoadScaled
function IMAGE_TBitmapLoadScaled(Filename: String; Scale: Extended; PremultiplyAlpha: Boolean): TBitmap;
var
    Handle: HBITMAP;
    HandleTemp: HBITMAP;
begin
    Handle := IMAGE_BitmapLoad(Filename);
    if Handle = 0 then
        Exit;

    HandleTemp := IMAGE_BitmapResize(Handle, Round(IMAGE_BitmapGetWidth(Handle) * Scale), Round(IMAGE_BitmapGetHeight(Handle) * Scale));
    IMAGE_BitmapFree(Handle);
    if HandleTemp = 0 then
        Exit;
    Handle := HandleTemp;

    if PremultiplyAlpha then
        IMAGE_BitmapAlphaPremultiply(Handle);

    Result := TBitmap.Create();
    Result.Handle := Handle;
end;



// Image/TBitmapResize
function IMAGE_TBitmapResize(Bitmap: TBitmap; Width: Integer; Height: Integer): Boolean;
var
    HandleTemp: HBITMAP;
begin
    if Bitmap.Handle = 0 then
        Exit;

    HandleTemp := IMAGE_BitmapResize(Bitmap.Handle, Width, Height);
    if HandleTemp = 0 then
        Exit;

    Bitmap.Handle := HandleTemp;
    Result := True;
end;



// IMAGE/TBitmapScale
function IMAGE_TBitmapScale(Bitmap: TBitmap; Scale: Extended): Boolean;
begin
    Result := IMAGE_TBitmapResize(Bitmap, Round(Bitmap.Width * Scale), Round(Bitmap.Height * Scale));
end;

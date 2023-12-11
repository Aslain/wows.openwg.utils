


//
// NETWORK
//

[Code]

// Network/Ping
function NETWORK_PingW_I(Hostname: String; Timeout: Integer): Integer;
external 'NETWORK_PingW@files:openwg.utils.dll cdecl setuponly';

function NETWORK_PingW_U(Hostname: String; Timeout: Integer): Integer;
external 'NETWORK_PingW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function NETWORK_Ping(Hostname: String; Timeout: Integer): Integer;
begin
    if IsUninstaller() then
        Result := NETWORK_PingW_U(Hostname, Timeout)
    else
        Result := NETWORK_PingW_I(Hostname, Timeout)
end;


// Network/Resolve
function NETWORK_ResolveW_I(Hostname: String): Integer;
external 'NETWORK_ResolveW@files:openwg.utils.dll cdecl setuponly';

function NETWORK_ResolveW_U(Hostname: String): Integer;
external 'NETWORK_ResolveW@{app}\{#OPENWGUTILS_DIR_UNINST}\openwg.utils.dll cdecl uninstallonly';

function NETWORK_Resolve(Hostname: String): Integer;
begin
    if IsUninstaller() then
        Result := NETWORK_ResolveW_U(Hostname)
    else
        Result := NETWORK_ResolveW_I(Hostname)
end;

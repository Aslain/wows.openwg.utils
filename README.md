# OpenWG.Utils

A set of tools that help in the development of modpacks and other WoT-related applications.

This project provides several ways to use it features:

* C API
* C# assembly
* InnoSetup script

## Example

### Json

InnoSetup code

```pascal
procedure TestJson;
var
  Handle: Integer;
begin
  Handle := JSON_FileOpen('meow.json', True);
  if Handle <> 0 then
  begin
     JSON_SetBool(Handle,'/meow',True);  // must start with /
     JSON_SetBool(Handle,'/gaw', False);
     JSON_SetBool(Handle,'/krya/krya/krya', False);
     JSON_FileClose(Handle);             // save changes to the file and close it, 
                                         // after JSON_FileClose() the file handle is not valid anymore
  end
end;
```

Result

```json
{
    "gaw": false,
    "krya": {
        "krya": {
            "krya": false
        }
    },
    "meow": true
}
```

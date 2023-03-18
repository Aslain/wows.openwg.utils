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
     JSON_SetBool(Handle,'/meow',True);             // must start with /
     JSON_SetDouble(Handle,'/gaw', 1.3);
     JSON_SetInteger(Handle,'/krya/krya/krya', 42);
     JSON_SetString(Handle,'/chyk/chyryk', 'aaa');
     JSON_FileClose(Handle);                        // save changes to the file and close it, 
                                                    // after JSON_FileClose() the file handle is not valid anymore
  end
end;
```

Result

```json
{
  "chyk" : 
  {
    "chyryk" : "aaa"
  },
  "gaw" : 1.3,
  "krya" : 
  {
    "krya" : 
    {
      "krya" : 42
    }
  },
  "meow" : true
}
```

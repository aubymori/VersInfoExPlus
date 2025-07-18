@echo off

::-------------------------------------------------------------------------------------------------

set "base_fname=myuuids"

set "VERSINFOEX_TYPELIB_VERS=1.0"

set "VERSINFOEX_INTERFACE_UUID=81C8CE7B-1C76-47DD-B20B-BD03AF7ED134"
set "VERSINFOEX_TYPELIB_UUID=07DA574F-FFC7-46FE-93BE-B8498ADFB9D0"
set "VERSINFOEX_CLASS_UUID=26B48C81-DAA1-4371-9441-2D8EC2A0B0F2"

set "VERSINFOEX_INTERFACE_DESC=IVersInfoShlExt Interface"
set "VERSINFOEX_TYPELIB_DESC=VersInfoEx Type Library"
set "VERSINFOEX_CLASS_DESC=VersInfoShlExt Class"

set ThreadingModel=Apartment

::-------------------------------------------------------------------------------------------------

if exist "%base_fname%.h" del "%base_fname%.h"

(echo #define VERSINFOEX_TYPELIB_VERS         %VERSINFOEX_TYPELIB_VERS%)        >>  "%base_fname%.h"
(echo.)                                                                         >>  "%base_fname%.h"
(echo #define VERSINFOEX_INTERFACE_UUID       %VERSINFOEX_INTERFACE_UUID%)      >>  "%base_fname%.h"
(echo #define VERSINFOEX_TYPELIB_UUID         %VERSINFOEX_TYPELIB_UUID%)        >>  "%base_fname%.h"
(echo #define VERSINFOEX_CLASS_UUID           %VERSINFOEX_CLASS_UUID%)          >>  "%base_fname%.h"
(echo.)                                                                         >>  "%base_fname%.h"
(echo #define VERSINFOEX_INTERFACE_DESC       "%VERSINFOEX_INTERFACE_DESC%")    >>  "%base_fname%.h"
(echo #define VERSINFOEX_TYPELIB_DESC         "%VERSINFOEX_TYPELIB_DESC%")      >>  "%base_fname%.h"
(echo #define VERSINFOEX_CLASS_DESC           "%VERSINFOEX_CLASS_DESC%")        >>  "%base_fname%.h"

::-------------------------------------------------------------------------------------------------

if exist "%base_fname%.rgs" del "%base_fname%.rgs"

(echo HKCR)                                                                          >>  "%base_fname%.rgs"
(echo {)                                                                             >>  "%base_fname%.rgs"
(echo     NoRemove CLSID)                                                            >>  "%base_fname%.rgs"
(echo     {)                                                                         >>  "%base_fname%.rgs"
(echo         ForceRemove {%VERSINFOEX_CLASS_UUID%} = s '%VERSINFOEX_CLASS_DESC%')   >>  "%base_fname%.rgs"
(echo         {)                                                                     >>  "%base_fname%.rgs"
(echo             InprocServer32 = s '%%MODULE%%')                                   >>  "%base_fname%.rgs"
(echo             {)                                                                 >>  "%base_fname%.rgs"
(echo                 val ThreadingModel = s '%ThreadingModel%')                     >>  "%base_fname%.rgs"
(echo             })                                                                 >>  "%base_fname%.rgs"
(echo         })                                                                     >>  "%base_fname%.rgs"
(echo     })                                                                         >>  "%base_fname%.rgs"
(echo     NoRemove *)                                                                >>  "%base_fname%.rgs"
(echo     {)                                                                         >>  "%base_fname%.rgs"
(echo         NoRemove shellex)                                                      >>  "%base_fname%.rgs"
(echo         {)                                                                     >>  "%base_fname%.rgs"
(echo             NoRemove PropertySheetHandlers)                                    >>  "%base_fname%.rgs"
(echo             {)                                                                 >>  "%base_fname%.rgs"
(echo                 {%VERSINFOEX_CLASS_UUID%})                                     >>  "%base_fname%.rgs"
(echo             })                                                                 >>  "%base_fname%.rgs"
(echo         })                                                                     >>  "%base_fname%.rgs"
(echo     })                                                                         >>  "%base_fname%.rgs"
(echo })                                                                             >>  "%base_fname%.rgs"

::-------------------------------------------------------------------------------------------------

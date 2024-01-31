@echo off
SETLOCAL EnableDelayedExpansion

cls

:: CPP compilation settings
SET CC="../cw/mwcceppc.exe"
SET CFLAGS=-I- -i %cd% -i "../source" -i "../source/game" -i "../engine"  -O2,p -opt loop,peep,schedule -inline auto -enum int -proc gekko -fp hard -rostr -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4 -rtti off 
SET DEFINE=

::: CPP Sources
%CC% %CFLAGS% -c -o "build/mkw.o" "mkw.cpp"
%CC% %CFLAGS% -c -o "build/kamek.o" "kamekLoader.cpp"

:: Link
echo Linking... %time%
"../Kamek" "build/mkw.o" "build/kamek.o" -static=0x80004000 -output-code=Loader.pul

if %ErrorLevel% equ 0 (
	del build\*.o
)

:end
ENDLOCAL
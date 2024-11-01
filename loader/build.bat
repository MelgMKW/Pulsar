@echo off
SETLOCAL EnableDelayedExpansion
cls
del build\*.o

:: CPP compilation settings
SET CC="../cw/mwcceppc.exe"
SET CFLAGS=-I- -i %cd% -i "../KamekInclude" -i "../GameSource" -i "../GameSource/MarioKartWii" -i PulsarEngine ^
  -opt all -inline auto -enum int -proc gekko -fp hard -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4 %cwDWARF%
SET DEFINE=

::: CPP Sources
%CC% %CFLAGS% -c -o "build/mkw.o" "mkw.cpp"
%CC% %CFLAGS% -c -o "build/kamek.o" "kamekLoader.cpp"

:: Link
echo Linking... %time%
"../KamekLinker/Kamek.exe" "build/mkw.o" "build/kamek.o" -static=0x80004000 -output-code=Loader.pul

:end
ENDLOCAL
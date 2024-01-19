@echo off
SETLOCAL EnableDelayedExpansion

cls
del build\*.o

:: Destination (change as necessary)
SET "SOURCE=Pulsar"
SET "RIIVO=C:\Users\admin\Documents\Dolphin Emulator\Load\Riivolution\Pulsar"
SET "ENGINE=C:\Modding\Coding\Kamek\Engine\engine"
echo %RIIVO%


:: CPP compilation settings
SET CC="../engine/cw/mwcceppc.exe"
SET CFLAGS=-I- -i "../engine/engine" -i "../engine/source" -i "../engine/source/game" -i Pulsar ^
  -opt all -inline auto -enum int -proc gekko -fp hard -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4
SET DEFINE=

:: CPP Sources
SET CPPFILES=
for /R Pulsar %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"

:: Compile CPP
%CC% %CFLAGS% -c -o "build/kamek.o" "%ENGINE%\kamek.cpp"

SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    ::echo "Compiling %%H..."
    %CC% %CFLAGS% %DEFINE% -c -o "build/%%~nH.o" "%%H"
    SET "OBJECTS=build/%%~nH.o !OBJECTS!"
)

:: Link
echo Linking... %time%
"../engine/Kamek" "build/kamek.o" %OBJECTS% -dynamic -externals="../engine/source/symbols.txt" -versions="../engine/source/versions.txt" -output-combined=build\Code.bin >nul

if %ErrorLevel% equ 0 (
    xcopy /Y build\*.bin "%RIIVO%\Binaries" >nul
    echo Binaries copied
)

:end
ENDLOCAL
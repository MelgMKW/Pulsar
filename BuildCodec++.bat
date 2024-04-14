SETLOCAL EnableDelayedExpansion
@echo off
cls
del build\*.o

SET "debug="
SET "cwDWARF="
if "%1" equ "-d" SET "debug=-debug -map=^"C:\Users\admin\Documents\Dolphin Emulator\Maps\RMCP01.map^" -readelf=^"C:\MinGW\bin\readelf.exe^""
if "%1" equ "-d" SET "cwDWARF=-g"


:: Destination (change as necessary)
SET "SOURCE=Pulsar"
SET "RIIVO=I:\Users\Omar\Desktop\OptPack Dolphin\Dolphin-x64\User\Load\Riivolution\optpackghost"
SET "ENGINE=I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\KamekInclude"
SET "CREATOR=I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\PulsarPackCreator\Resources"
echo %RIIVO%


:: C/CPP compilation settings
SET CC="mwcceppc.exe"
SET CFLAGS=-I- -i "I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\KamekInclude" -i "I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\GameSource" -i "I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\GameSource\MarioKartWii" -i PulsarEngine ^
  -opt all -inline auto -enum int -proc gekko -fp hard -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4 %cwDWARF%
SET DEFINE=

:: CPP Sources
SET CPPFILES=
for /R PulsarEngine %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"

:: C Sources
SET CFILES=
for /R PulsarEngine %%f in (*.c) do SET "CFILES=%%f !CFILES!"

:: Compile CPP
%CC% %CFLAGS% -c -o "build/kamek.o" "%ENGINE%\kamek.cpp"

:: Compile C files
FOR %%H IN (%CFILES%) DO (
    ::echo "Compiling %%H..."
    %CC% %CFLAGS% %DEFINE% -c -o "build/%%~nH.o" "%%H"
)

SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    ::echo "Compiling %%H..."
    %CC% %CFLAGS% %DEFINE% -c -o "build/%%~nH.o" "%%H"
    SET "OBJECTS=build/%%~nH.o !OBJECTS!"
)

:: Link
echo Linking... %time%
"Kamek.exe" "build/kamek.o" %OBJECTS% %debug% -dynamic -externals="I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\GameSource\symbols.txt" -versions="I:\Users\Omar\Desktop\Mario_Kart_Wii\OptPack_Files\BuilderPulsar\Pulsar\GameSource\versions.txt" -output-combined=build\Code.pul

if %ErrorLevel% equ 0 (
    xcopy /Y build\*.pul "%RIIVO%\Binaries" >nul
    xcopy /Y build\*.pul "%CREATOR%" >nul
    echo Binaries copied
)

:end
ENDLOCAL
PAUSE

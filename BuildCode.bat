@echo off
SETLOCAL EnableDelayedExpansion

cls
del build\*.o

:: Destination (change as necessary)
SET "SOURCE=Pulsar"
SET "RIIVO=D:\Documents\Dolphin Emulator\Load\Pulsar"
SET "RELEASE=D:\Modding\Coding\Kamek\Pulsar\releases"
echo %RIIVO%


:: CPP compilation settings
SET CC="../engine/cw/mwcceppc.exe"
SET CFLAGS=-I- -i "../engine/engine" -i "../engine/source" -i "../engine/source/game" -i code -O2,p^
  -opt loop,peep,schedule  -inline auto -enum int -proc 750 -fp hard -rostr -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4 -rtti off 
SET DEFINE=

:: CPP Sources
SET CPPFILES=
for /R code %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"

:: Compile CPP
%CC% %CFLAGS% -c -o "build/kamek.o" "D:\Modding\Coding\Kamek\Engine\engine\kamek.cpp"

SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    ::echo "Compiling %%H..."
    %CC% %CFLAGS% %DEFINE% -c -o "build/%%~nH.o" "%%H"
    SET "OBJECTS=build/%%~nH.o !OBJECTS!"
)

:: Link
echo Linking... %time%
"../engine/Kamek" "build/kamek.o" %OBJECTS% -dynamic -externals="../engine/source/symbols.txt" -versions="../engine/source/versions.txt" -output-kamek=build\$KV$.bin >nul

if %ErrorLevel% equ 0 (
    xcopy /Y build\*.bin "%RELEASE%\Binaries" >nul
    cd "D:\Modding\Coding\Kamek\Pulsar\resources" >nul
    xcopy /Y /S "%RELEASE%\Binaries" "%RIIVO%\Binaries" >nul
    xcopy /Y /S "%RELEASE%\Binaries" "D:\Documents\Dolphin Emulator\Load\varietypack\Binaries" >nul
    echo Binaries copied
)

:end
ENDLOCAL
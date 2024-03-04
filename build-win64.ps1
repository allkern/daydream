git fetch --all --tags

$VERSION_TAG = git describe --always --tags --abbrev=0
$COMMIT_HASH = git rev-parse --short HEAD
$OS_INFO = (Get-WMIObject win32_operatingsystem).caption + " " + (Get-WMIObject win32_operatingsystem).version + " " + (Get-WMIObject win32_operatingsystem).OSArchitecture

$IMGUI_DIR = ".\imgui"
$SDL2_DIR = ".\SDL2-2.26.5\x86_64-w64-mingw32"
$DDREAM_DIR = ".\src"

Write-Host -NoNewline "Building Daydream core... "

Set-Location build

gcc -c `
    -I"`"..\$($DDREAM_DIR)`"" `
    "..\src\holly\*.c" `
    "..\src\*.c" `
    -Ofast -ffast-math -Wno-incompatible-pointer-types

Write-Output "done"

Set-Location ..

mkdir -Force -Path bin > $null

c++ -I"`"$($DDREAM_DIR)`"" `
    -I"`"$($DDREAM_DIR)\frontend`"" `
    -I"`"$($IMGUI_DIR)`"" `
    -I"`"$($IMGUI_DIR)\backends`"" `
    -I"`"$($SDL2_DIR)\include`"" `
    -I"`"$($SDL2_DIR)\include\SDL2`"" `
    ".\res\*.res" `
    ".\build\*.o" `
    ".\frontend\*.cpp" `
    -o ".\bin\ddream.exe" `
    -DREP_VERSION="`"$($VERSION_TAG)`"" `
    -DREP_COMMIT_HASH="`"$($COMMIT_HASH)`"" `
    -DOS_INFO="`"$($OS_INFO)`"" `
    -L"`"$($SDL2_DIR)\lib`"" `
    -m64 -lSDL2main -lSDL2 -ldwmapi `
    -Wall -pedantic -ffast-math -Ofast -g

# gcc -I"`"$($DDREAM_DIR)`"" `
#     -I"`"$($SDL2_DIR)\include`"" `
#     -I"`"$($SDL2_DIR)\include\SDL2`"" `
#     "src\holly\*.c" `
#     "src\*.c" `
#     "main.c" `
#     -o ".\bin\ddream.exe" `
#     -DREP_VERSION="`"$($VERSION_TAG)`"" `
#     -DREP_COMMIT_HASH="`"$($COMMIT_HASH)`"" `
#     -DOS_INFO="`"$($OS_INFO)`"" `
#     -L"`"$($SDL2_DIR)\lib`"" `
#     -m64 -lSDL2main -lSDL2 `
#     -Wall -pedantic -ffast-math -Ofast -g `
#     -Wno-incompatible-pointer-types

Copy-Item -Path "sdl2-win64/SDL2.dll" -Destination "bin"
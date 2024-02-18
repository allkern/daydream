if (Test-Path "SDL2-2.26.5") {
    Remove-Item -Recurse "SDL2-2.26.5"
}

$SDL2_URL = "https://github.com/libsdl-org/SDL/releases/download/release-2.26.5/SDL2-devel-2.26.5-mingw.zip"
$WIN64_URL = "https://github.com/libsdl-org/SDL/releases/download/release-2.26.5/SDL2-2.26.5-win32-x64.zip"

Invoke-WebRequest -URI $SDL2_URL -OutFile "sdl2.zip"
Expand-Archive "sdl2.zip" -DestinationPath "." -Force

Invoke-WebRequest -URI $WIN64_URL -OutFile "sdl2-win64.zip"
Expand-Archive "sdl2-win64.zip" -DestinationPath "sdl2-win64" -Force

Remove-Item "sdl2.zip"
Remove-Item "sdl2-win64.zip"
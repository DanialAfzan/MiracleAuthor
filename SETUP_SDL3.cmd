@echo off
cd /d "%~dp0"
echo.
echo Miracle Author - SDL3 developer SDK setup
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\setup_sdl3.ps1"
echo.
pause

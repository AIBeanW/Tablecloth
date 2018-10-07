@echo off

setlocal enableextensions

set CURL=%~dp0curl.exe

echo get Firefox
echo.
echo Downloading Firefox ESR installer

"%CURL%" -L -f -# -o firefox.exe "https://download.mozilla.org/?product=firefox-esr-latest&os=win&lang=zh-CN" %$X%

if errorlevel 1 (
	echo Error code: %ErrorLevel%
	pause
	exit
) else (echo Finish!)

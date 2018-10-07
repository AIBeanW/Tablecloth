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

echo.
echo Unpacking the installer and deleting unnecessary files

7z x -y -o..\Firefox\App firefox.exe > nul
del /Q firefox.exe
ren ..\Firefox\App\core Firefox
del /Q ..\Firefox\App\setup.exe
rmdir /S /Q ..\Firefox\App\Firefox\dictionaries
rmdir /S /Q ..\Firefox\App\Firefox\uninstall
del /Q ..\Firefox\App\Firefox\browser\blocklist.xml
del /Q ..\Firefox\App\Firefox\browser\crashreporter-override.ini
del /Q ..\Firefox\App\Firefox\crashreporter.*
del /Q ..\Firefox\App\Firefox\maintenanceservice*.*
del /Q ..\Firefox\App\Firefox\update*.*


echo add config
mkdir ..\Firefox\App\DefaultData\profile\ > nul
copy /Y profile\* ..\Firefox\App\DefaultData\profile\ > nul
copy /Y firefox-portable\* ..\Firefox\ > nul


echo Complete!
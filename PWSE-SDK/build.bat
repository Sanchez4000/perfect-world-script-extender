@echo off
REM ============================================================
REM  PWSE plugin build button.
REM  Собирает src\*.c -> build\<имя_папки>.so (linux i386) через Docker.
REM  Требуется только установленный Docker Desktop.
REM  Имя .so = имя этой папки (скопировал SDK -> переименовал -> собрал).
REM ============================================================
setlocal
set "HERE=%~dp0"
if "%HERE:~-1%"=="\" set "HERE=%HERE:~0,-1%"
for %%I in ("%HERE%") do set "NAME=%%~nxI"
set "IMAGE=pwse-toolchain"

echo [build] plugin: %NAME%
echo [build] checking toolchain image...
docker image inspect %IMAGE% >nul 2>&1
if errorlevel 1 echo [build] building toolchain image (first run)...
if errorlevel 1 docker build -t %IMAGE% "%HERE%\toolchain"
if errorlevel 1 echo [build] toolchain build FAILED
if errorlevel 1 exit /b 1

echo [build] compiling %NAME%.so ...
docker run --rm -v "%HERE%:/src" -w /src %IMAGE% sh -c "mkdir -p build && gcc -m32 -D_FILE_OFFSET_BITS=64 -shared -fPIC -O2 -Wall -fno-stack-protector -Iinclude src/*.c -o build/%NAME%.so"
if errorlevel 1 echo [build] compile FAILED
if errorlevel 1 exit /b 1

echo [build] OK: build\%NAME%.so

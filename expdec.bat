@echo off

set PLATFORM=esp32
set TOOLCHAIN=%HOME%/.platformio/packages/toolchain-xtensa32
set ADDR2LINE=%TOOLCHAIN%/bin/xtensa-esp32-elf-addr2line
set ELFFILE=.pio/build/%PLATFORM%/firmware.elf

rem echo on

echo.

@pushd %~dp0
%ADDR2LINE% -pfiaC -e %ELFFILE% %*
@popd


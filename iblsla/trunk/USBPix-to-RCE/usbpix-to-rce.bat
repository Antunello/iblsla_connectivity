@echo off
prompt ]
call "c:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"
echo on
mkdir %1.rce\
Example1 %1 %1.rce\
pause

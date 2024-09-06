@ECHO off

ECHO Installing dependencies...
conan install --profile=windows.txt --build=missing .

ECHO Building project...
conan build .

ECHO Done.

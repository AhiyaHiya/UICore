@ECHO OFF

ECHO Creating Conan package...
conan create --user jaimerios --channel alpha1 .
ECHO Done.
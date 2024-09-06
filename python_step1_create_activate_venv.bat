@ECHO OFF

SET PYTHON_PATH="C:\Program Files\Python311\python.exe"
SET VENV_PATH=venv_py311\Scripts\activate.bat

ECHO Checking Python installation...
IF NOT EXIST %PYTHON_PATH% (
    ECHO Python 3.11 is not installed at %PYTHON_PATH%. Please install it and try again.
    EXIT /B
)
ECHO Python installation found.

ECHO Creating Python virtual environment...
%PYTHON_PATH% -m venv venv_py311

IF NOT EXIST %VENV_PATH% (
    ECHO Failed to create Python virtual environment. Please check your Python installation.
    EXIT /B
)
ECHO Python virtual environment created.

ECHO Activating Python virtual environment...
CALL %VENV_PATH%

ECHO Checking Python version...
python --version

ECHO Checking Conan installation...
WHERE /Q conan
IF ERRORLEVEL 1 (
    ECHO Conan is not installed or not found in PATH. Please install it and try again.
    EXIT /B
)
ECHO Conan installation found.

ECHO Checking Conan version...
conan --version

@REM ECHO Deactivate Python virtual environment...
@REM venv_py311\Scripts\deactivate.bat

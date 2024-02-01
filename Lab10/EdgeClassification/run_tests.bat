@echo off
SET progPath=.\prog.exe
SET inputDir=.\
SET outputDir=.\

:: Get the current directory and store it in a variable
CD
SET currentDir=%CD%

ECHO.
ECHO Running the tests in directory: %currentDir% for program %progPath% with inputs from %inputDir% and outputs to %outputDir% 
ECHO.

FOR %%i IN (1,2,3,4) DO (
    IF EXIST %outputDir%\mout%%i.txt DEL %outputDir%\mout%%i.txt
    %progPath% < %inputDir%\in%%i.txt > %outputDir%\mout%%i.txt
    FC %outputDir%\mout%%i.txt %outputDir%\out%%i.txt
)
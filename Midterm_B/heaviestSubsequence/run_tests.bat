@echo off
SET progPath=C:\Users\jakub\Desktop\ADS\Midterm_B\heaviestSubsequence\prog.exe
SET inputDir=C:\Users\jakub\Desktop\ADS\Midterm_B\heaviestSubsequence
SET outputDir=C:\Users\jakub\Desktop\ADS\Midterm_B\heaviestSubsequence

FOR %%i IN (1,2,3,4) DO (
    IF EXIST %outputDir%\mout%%i.txt DEL %outputDir%\mout%%i.txt
    %progPath% < %inputDir%\in%%i.txt > %outputDir%\mout%%i.txt
    FC %outputDir%\mout%%i.txt %outputDir%\out%%i.txt
)
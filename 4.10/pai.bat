@echo off
:again
echo again
da
a
aa
fc a.out aa.out
if not errorlevel 1 goto again
pause
goto again
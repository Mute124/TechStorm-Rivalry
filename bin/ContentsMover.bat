echo off
set file=%1
set out=%2
echo %file%
echo %out%

xcopy %USERPROFILE%\source\repos\TechStorm-Rivalry\%file% %USERPROFILE%\source\repos\TechStorm-Rivalry\bin\%out% /E

	
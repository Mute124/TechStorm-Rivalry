set folder=%1

powershell Compress-Archive %USERPROFILE%\source\repos\TechStorm-Rivalry\bin\%folder% publish.zip

rd %USERPROFILE%\source\repos\TechStorm-Rivalry\bin\%folder% /s
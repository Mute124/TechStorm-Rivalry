cd C:\Minero\w64devkit

clear
$1 = filename
echo Compiling now...
make $1

echo Compiled, Running now
./"$1.exe"

echo done



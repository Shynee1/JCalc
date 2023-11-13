@echo off

REM Set current directory to where batch file is located
pushd %~dp0

set "newPath=C:\Program Files\jcalc"

REM Create main directory
if NOT exist "%newPath%" (
	echo '%newPath%' not found
	echo Creating new directory...
	MKDIR "%newPath%"
	if exist "%newPath%" echo Directory sucessfully created
)

REM Compile the program into an exe
if NOT exist "%newPath%\jcalc.exe" (
	echo 'jcalc.exe' not found
	echo Compiling program...
	g++ -I headers -c source/main.cpp -o bin/main.o
	g++ -I headers -c source/parser.cpp -o bin/parser.o
	g++ -I headers -c source/lexer.cpp -o bin/lexer.o
	g++ -o jcalc bin/main.o bin/parser.o bin/lexer.o

	MOVE "jcalc.exe" "%newPath%"
	if exist "%newPath%" echo Program sucessfully compiled
)

popd

pause
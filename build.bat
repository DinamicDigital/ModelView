@echo off

set WindowsLib=opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

:: to add a library include append /I ../libs/<library include folder> to the following line: 
set IncludeDirs=/I ../libs/GLFW/include
:: to add a library, just append the location of the .lib file you need onto this line:
set Libraries=%WindowsLib% ../libs/GLFW/lib-vc2019/glfw3.lib

mkdir ./bin/
cd ./bin
:: /MD is IMPORTANT, wont use GLFW without it.
cl ../src/build.c /Fe%cd%/ModelView /MD %IncludeDirs% %Libraries% /link 
call ModelView.exe
cd ..


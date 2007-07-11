REM Generates .lib files for Borland C++

implib opengl32.lib %SYSTEMROOT%\system32\opengl32.dll
implib glu32.lib %SYSTEMROOT%\system32\glu32.dll
implib winmm.lib %SYSTEMROOT%\system32\winmm.dll

implib glut32.lib ..\glut32.dll

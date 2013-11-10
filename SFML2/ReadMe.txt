-------------- Clean: Release in SFML2 (compiler: GNU GCC Compiler)---------------

Cleaned "SFML2 - Release"

-------------- Build: Release in SFML2 (compiler: GNU GCC Compiler)---------------

mingw32-g++.exe -std=c++11 -Wall  -O2  -std=c++11 -Wall   -ID:\CodeBlocks\SFML-2.1\include  -c D:\Projects\C++\jadegrfx\SFML2\main01.cpp -o obj\Release\main01.o
mingw32-g++.exe -LD:\CodeBlocks\SFML-2.1\lib  -o bin\Release\SFML2.exe obj\Release\main01.o   -s  D:\CodeBlocks\SFML-2.1\lib\libsfml-network.a D:\CodeBlocks\SFML-2.1\lib\libsfml-audio.a D:\CodeBlocks\SFML-2.1\lib\libsfml-graphics.a D:\CodeBlocks\SFML-2.1\lib\libsfml-window.a D:\CodeBlocks\SFML-2.1\lib\libsfml-system.a D:\CodeBlocks\SFML-2.1\lib\libsfml-main.a  -mwindows
Output size is 509.00 KB
Process terminated with status 0 (0 minutes, 5 seconds)
0 errors, 0 warnings (0 minutes, 5 seconds)

I use UPX to compress it down to 141 KB
upx -9 SFML2.exe
Simple SDL1 Test.

Compile with:

g++ test.cpp $(sdl-config --libs --cflags) -ldl -lSDL_image -lSDL_ttf -o test

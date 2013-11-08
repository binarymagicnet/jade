Simple SDL Test.

Compile with:

g++ -ldl $(sdl-config --libs --cflags)  -lSDL_image -lSDL_ttf test.cpp -o test

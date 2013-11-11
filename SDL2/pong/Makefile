all:pong

CC = g++
LDFLAGS = $(shell sdl2-config --libs --cflags) -ldl

pong:
	$(CC) -Wno-unused $@.cpp $(LDFLAGS) -o $@

clean:
	@rm -f pong


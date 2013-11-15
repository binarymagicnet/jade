all:test

CC = g++
LDFLAGS = $(shell sdl-config --libs --cflags) -ldl

test:
	$(CC) -Wall $@.cpp $(LDFLAGS) -o $@

clean:
	@rm -f pong


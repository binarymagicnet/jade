all:pong

CC = g++
LDFLAGS = $(shell sdl2-config --libs --cflags) -ldl

pong:
	$(CC) -Wall $@.cpp $(LDFLAGS) -o $@

clean:
	@rm -f pong


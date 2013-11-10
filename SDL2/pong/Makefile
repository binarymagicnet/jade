all:pong

CC = g++
LDFLAGS = $(shell sdl2-config --libs --cflags) -ldl

pong:
	 $(CC) $@.cpp $(LDFLAGS) -o $@
 


all: help

CC = g++
LDFLAGS = $(shell wx-config --libs --cflags) -ldl
PLATFORM := $(shell uname -s)

help:
	$(CC) -Wall $@.cpp $(LDFLAGS) -o $@

clean:
	@$(RM) -f help
	@$(RM) -rf help.app


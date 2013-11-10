all: help

CC = g++
LDFLAGS = $(shell wx-config --libs --cflags) -ldl
PLATFORM := $(shell uname -s)

help:
	$(CC) $@.cpp $(LDFLAGS) -o $@

clean:
	@$(RM) -f help
	@$(RM) -rf help.app


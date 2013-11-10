all: help

CC = g++
LDFLAGS = $(shell wx-config --libs --cflags)
PLATFORM := $(shell uname -s)

help:
	$(CC) $(LDFLAGS) $@.cpp -o $@

clean:
	@$(RM) -f help
	@$(RM) -rf help.app


all:
	cc `pkg-config --cflags gtk+-3.0` main.c -o bin/lightwebsearch `pkg-config --libs gtk+-3.0` -rdynamic -O3

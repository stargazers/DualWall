all: dualwall

dualwall: main.c
	gcc -Wall -g -o dualwall main.c `imlib2-config --cflags` `imlib2-config --libs`


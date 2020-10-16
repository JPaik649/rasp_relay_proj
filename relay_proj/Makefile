CC=gcc
CFLAGS=-Wall -Werror -std=c99 -g -lpigpio -lrt
DEPS=relay.h
OBJ=main.o relay.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

relaymake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

CC=gcc
CFLAGS=-g -Wall -Werror -Wno-array-bounds
OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))
HEADERS=$(wildcard *.h)

all: ngram
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -g -c -o $@
ngram: ngram.o main.o 
	$(CC) $(CFLAGS) ngram.o main.o -o ngram

clean:
	rm -f ngram $(OBJECTS)

VTENCDIR = ../..

CC = gcc
CFLAGS ?= -Wall -O3

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: default
default: all

.PHONY: all
all: unit_tests

%.o: %.c
	${CC} -c $(CFLAGS) $<

unit_tests: $(OBJ)
	$(CC) $(CFLAGS) $^ $(VTENCDIR)/libvtenc.a -o $@

.PHONY: clean
clean:
	rm -f *.o unit_tests

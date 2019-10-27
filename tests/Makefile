VTENCDIR = ..

CC = gcc
CFLAGS ?= -Wall -O3

.PHONY: default
default: all

.PHONY: all
all: timestamps gov2

%.o: %.c
	${CC} -c $(CFLAGS) $<

timestamps: timestamps.o
	$(CC) $(CFLAGS) $^ $(VTENCDIR)/libvtenc.a -o $@

gov2: gov2.o
	$(CC) $(CFLAGS) $^ $(VTENCDIR)/libvtenc.a -o $@

.PHONY: clean
clean:
	rm -f *.o timestamps gov2

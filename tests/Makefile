# Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
# Licensed under the MIT License.
# See LICENSE file in the project root for full license information.

VTENCDIR = ..

CC = gcc
CFLAGS ?= -std=c99 -Wall -O3

.PHONY: default
default: all

.PHONY: all
all: timestamps gov2 testbinseq

%.o: %.c
	${CC} -c $(CFLAGS) $<

timestamps: encdec.o timestamps.o
	$(CC) $(CFLAGS) $^ $(VTENCDIR)/libvtenc.a -o $@

gov2: encdec.o gov2.o
	$(CC) $(CFLAGS) $^ $(VTENCDIR)/libvtenc.a -o $@

testbinseq: encdec.o testbinseq.o
	$(CC) $(CFLAGS) $^ $(VTENCDIR)/libvtenc.a -o $@

.PHONY: clean
clean:
	rm -f *.o timestamps gov2 testbinseq

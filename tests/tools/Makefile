# Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
# Licensed under the MIT License.
# See LICENSE file in the project root for full license information.

CC = gcc
CFLAGS ?= -std=c99 -Wall -O3
TINYMTOBJS = tinymt32.o tinymt64.o

.PHONY: default
default: all

.PHONY: all
all: genrandseq

%.o: %.c
	${CC} -c $(CFLAGS) $<

genrandseq: $(TINYMTOBJS) genrandseq.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o genrandseq

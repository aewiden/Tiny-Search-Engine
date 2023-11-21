# Makefile for 'indexer' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

C = ../common
L = ../libcs50

PROGS = indexer indextest indexcmp
LIBS =
LLIBS = $C/common.a $L/libcs50-given.a

# add -DAPPEST for functional tracking report
# add -DMEMTEST for memory tracking report
# (and run `make clean; make` whenever you change this)
FLAGS = # -DAPPTEST # -DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
CC = gcc
MAKE = make

.PHONY: all test clean

########### default ##################

all: $(PROGS)

########### indexer ##################

# indexer source dependencies
indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indexcmp: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indexer.o: $C/index.h $C/pagedir.h $C/word.h
indexer.o: $L/webpage.h $L/file.h $L/mem.h $L/counters.h $L/hashtable.h
indextest.o: $C/index.h $C/pagedir.h $C/word.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: indexer testing.sh
	bash -v < testing.sh

# expects a file `test.names` to exist; it can contain any text.
valgrind: indextest test.names
	$(VALGRIND) ./indextest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f indexer
	rm -f core

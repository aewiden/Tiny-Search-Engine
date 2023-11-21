# Makefile for 'crawler' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

OBJS = crawler.o 
LIBS = ../libcs50/libcs50-given.a ../common/pagedir.o
# ../libcs50/file.o ../libcs50/mem.o ../libcs50/webpage.o ../libcs50/hashtable.o ../libcs50/bag.o ../libcs50/set.o

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

crawler: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

crawler.o: crawler.h ../libcs50/mem.h ../libcs50/bag.h ../libcs50/webpage.h ../libcs50/hashtable.h ../common/pagedir.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: crawler testing.sh
	bash -v < testing.sh

# expects a file `test.names` to exist; it can contain any text.
valgrind: crawlertest test.names
	$(VALGRIND) ./crawlertest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f crawler
	rm -f core

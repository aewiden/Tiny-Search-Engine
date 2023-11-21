# Makefile for 'common' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

L = ../libcs50

OBJS = index.o pagedir.o word.o
LIB = common.a

FLAGS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L
CC = gcc
MAKE = make

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

index.o: index.h $L/file.h $L/counters.h $L/hashtable.h 
pagedir.o: pagedir.h $L/webpage.h $L/file.h
word.o: word.h

clean:
	rm -f core
	rm -f $(LIB) *~ *.o















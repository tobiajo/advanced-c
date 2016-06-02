#!/bin/bash
gcc main.c -o main.o -c \
&& gcc hashtable.c -o hashtable.o -c \
&& gcc main.o hashtable.o \
&& rm *.o \
&& ./a.out \
&& rm a.out

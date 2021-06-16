CC      = gcc
CFLAGS  = -O2 -Wall -Wextra -Wpedantic -march=native
INFILE  = main.c
OUTFILE = assemble

default:
	$(CC) $(CFLAGS) $(INFILE) -o $(OUTFILE)

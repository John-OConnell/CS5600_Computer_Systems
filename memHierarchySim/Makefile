#
# Makefile / Memory Heirarchy Simulation - Part 1
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Oct 26, 2023
#
#

all: test

test: message.c test.c
	@gcc message.c test.c -o test

clean:
	@rm -f test messages/*
	@touch message.h message.c test.c


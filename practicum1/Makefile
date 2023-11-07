#
# Makefile / Practicum 1
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Nov 7, 2023
#
#

all: test

test: message.c messageTest.c dll.h dllTest.c
	@gcc message.c messageTest.c -o messageTest
	@gcc dllTest.c -o dllTest

clean:
	@rm -f messageTest messages/*
	@rm -f dllTest
	@touch message.h message.c messageTest.c


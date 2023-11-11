#
# Makefile / Practicum 1
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Nov 7, 2023
#
#

all: dllTest lruTest randTest

test: dllTest lruTest randTest

dllTest: dllTest.c
	@gcc dll.c dllTest.c -o dllTest

lruTest: message.c lruCache.c genRandWord.c cacheTest.c
	@gcc message.c lruCache.c genRandWord.c dll.c cacheTest.c -o lruTest

randTest: message.c randCache.c genRandWord.c cacheTest.c
	@gcc message.c randCache.c genRandWord.c dll.c cacheTest.c -o randTest

clean:
	@rm -f dllTest
	@rm -f lruTest
	@rm -f randTest
	@rm -f test messages/*

#
# Makefile / Practicum 1
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Nov 7, 2023
#
#

all: test eval

test: dllTest lruTest randTest

eval: lruEval randEval lruEvalLoc randEvalLoc

dllTest: dllTest.c
	@gcc dll.c dllTest.c -o dllTest

lruTest: message.c lruCache.c genRandWord.c dll.c cacheTest.c
	@gcc message.c lruCache.c genRandWord.c dll.c cacheTest.c -o lruTest

randTest: message.c randCache.c genRandWord.c dll.c cacheTest.c
	@gcc message.c randCache.c genRandWord.c dll.c cacheTest.c -o randTest

lruEval: message.c lruCache.c genRandWord.c dll.c cacheEval.c
	@gcc message.c lruCache.c genRandWord.c dll.c cacheEval.c -o lruEval

randEval: message.c randCache.c genRandWord.c dll.c cacheEval.c
	@gcc message.c randCache.c genRandWord.c dll.c cacheEval.c -o randEval

lruEvalLoc: message.c lruCache.c genRandWord.c dll.c cacheEvalLoc.c
	@gcc message.c lruCache.c genRandWord.c dll.c cacheEvalLoc.c -o lruEvalLoc

randEvalLoc: message.c randCache.c genRandWord.c dll.c cacheEvalLoc.c
	@gcc message.c randCache.c genRandWord.c dll.c cacheEvalLoc.c -o randEvalLoc

clean:
	@rm -f dllTest lruTest randTest lruEval randEval lruEvalLoc randEvalLoc
	@rm -f test messages/*
	@touch message.c lruCache.c randCache.c cacheTest.c cacheEval.c cacheEvalLoc.c dll.c dllTest.c genRandWord.c

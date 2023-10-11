#
# Makefile / Random Word Generation
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Oct 8, 2023
#
#

all: genRandWord multiprocessing cipher unittests


genRandWord: genRandWord-oconnell.c genRandWord-helper.c
	@gcc genRandWord-oconnell.c genRandWord-helper.c -o genRandWord

multiprocessing: multiprocessing.c
	@ gcc multiprocessing.c multiprocessing-helper.c queue.c polybius.c -o multiprocess

cipher: cipher.c polybius.c
	@gcc cipher.c polybius.c -o cipher

unittests: unittests.c
	@gcc unittests.c -o unittests

clean:
	@rm -f genRandWord multiprocess cipher unittests
	@touch genRandWord-oconnell.c genRandWord-helper.c cipher.c polybius.c multiprocessing.c unittests.c


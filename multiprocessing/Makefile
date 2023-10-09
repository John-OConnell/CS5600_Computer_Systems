#
# Makefile / Random Word Generation
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Oct 8, 2023
#
#

all: genRandWord multiprocessing cipher


genRandWord: genRandWord-oconnell.c genRandWord-helper.c
	@gcc genRandWord-oconnell.c genRandWord-helper.c -o genRandWord

multiprocessing: multiprocessing.c
	@ gcc multiprocessing.c queue.c polybius.c -o multiprocess

cipher: polybius.c cipher.c
	@gcc polybius.c cipher.c -o cipher


clean:
	@rm -f genRandWord multiprocess cipher
	@touch genRandWord-oconnell.c genRandWord-helper.c multiprocessing.c polybius.c cipher.c


#
# Makefile / Multithreading
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Oct 8, 2023
#
#

all: genRandWord multithreading unittests

genRandWord: genRandWord-oconnell.c genRandWord-helper.c
	@gcc genRandWord-oconnell.c genRandWord-helper.c -o genRandWord

multithreading: multithreading.c
	@gcc multithreading.c multithreading-helper.c queue.c polybius.c -o multithread

unittests: unittests.c
	@gcc unittests.c -o unittests

clean:
	@rm -f genRandWord multithread unittests
	@touch genRandWord-oconnell.c genRandWord-helper.c multithreading.c multithreading-helper.c polybius.c unittests.c


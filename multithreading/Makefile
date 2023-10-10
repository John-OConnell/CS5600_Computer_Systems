#
# Makefile / Multithreading
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Oct 8, 2023
#
#

all: genRandWord multithreading cipher


genRandWord: genRandWord-oconnell.c genRandWord-helper.c
	@gcc genRandWord-oconnell.c genRandWord-helper.c -o genRandWord

multithreading: multithreading.c
	@ gcc multithreading.c queue.c polybius.c -o multithread

cipher: polybius.c cipher.c
	@gcc polybius.c cipher.c -o cipher


clean:
	@rm -f genRandWord multithread cipher
	@touch genRandWord-oconnell.c genRandWord-helper.c multithreading.c polybius.c cipher.c


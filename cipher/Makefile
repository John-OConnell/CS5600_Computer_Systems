#
# Makefile / Create Cipher
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Sep 26, 2023
#
#

all: Cipher

Cipher: polybius.c cipher.c
	@gcc polybius.c cipher.c -o cipher

clean:
	@rm -f cipher
	@touch polybius.c cipher.c
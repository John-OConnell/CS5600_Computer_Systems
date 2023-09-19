all: genRand


genRand: genRand-oconnell.c
	@gcc genRand-oconnell.c genRand-helper.c -o genRand


clean:
	@rm -f genRand
	@touch genRand-oconnell.c genRand-helper.c

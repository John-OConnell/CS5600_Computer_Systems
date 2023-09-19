#
# Makefile / Memory Management
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Sep 16, 2023
#
#/

all: alloc-mem load-mem

alloc-mem: alloc-mem-oconnell.c
	@gcc alloc-mem-oconnell.c -o allocmem

load-mem: load-mem-oconnell.c
	@gcc load-mem-oconnell.c -o loadmem
clean:
	@rm -f allocmem loadmem
	@touch alloc-mem-oconnell.c load-mem-oconnell.c

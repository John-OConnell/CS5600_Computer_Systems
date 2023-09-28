#
# Makefile / Process Queue
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Sep 27, 2023
#
#

all: Queue

Queue: queue.c queuetest.c
	@gcc queue.c queuetest.c -o qtest

clean:
	@rm -f qtest
	@touch queue.c queuetest.c

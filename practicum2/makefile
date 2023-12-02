#
# Makefile / Practicum 2
#
# John O'Connell / CS5600 / Northeastern University
# Fall 2023 / Nov 28, 2023
#
#

all: server client

server: server.c server-helper.c
	gcc server.c server-helper.c -o server

client: client.c client-helper.c
	gcc client.c client-helper.c -o rfs

clean:
	rm -f server rfs
	touch client.c client-helper.c server.c server-helper.c

rfsclean:
	find rfsys/ -maxdepth 2 -type f ! -name '.*' -delete

//
// client.c / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "client-helper.h"

int main(int argc, char* argv[])
{
  // check that correct # of arguments are passed in
	if (argc < 3 || argc > 4)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}

  // get necessary variables from input
	char* command = argv[1];

  // process input
	if (strcmp(command, "WRITE") == 0)
	{
    char* local_file_path = argv[2];
    char* remote_file_path;
    if (argc == 4)
    {
      remote_file_path = argv[3];
    }
    else
    {
      remote_file_path = argv[2];
    }

		rfs_write(local_file_path, remote_file_path);
		return 0;
	}
  else
  {
    printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
  }
  return 0;
}

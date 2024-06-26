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
  // Check that correct # of arguments are passed in
	if (argc < 2 || argc > 5)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}

  // Get command from input
	char* command = argv[1];

  // Process input
	if (strcmp(command, "WRITE") == 0)
	{
    char* local_file_path = argv[2];
    char* remote_file_path;
    // Write command can't have 2 or 5 arguments
    if (argc == 2 || argc == 5)
    {
      printf("INVALID INPUT - See Below for Help\n\n");
		  print_help();
		  return -1;
    }
    else if (argc == 4)
    {
      remote_file_path = argv[3];
    }
    else
    {
      remote_file_path = argv[2];
    }

		return rfs_write(local_file_path, remote_file_path);

	}
	else if (strcmp(command, "GET") == 0)
	{
    char* remote_file_path = argv[2];
    char* local_file_path;

    // Check if a version number is provided
    int versionNumber = -1;  // Default version number

    // Get command can't have 2
    if (argc == 2)
    {
      printf("INVALID INPUT - See Below for Help\n\n");
		  print_help();
		  return -1;
    }
    else if (argc >= 4)
    {
      // Attempt to parse the last argument as a version number
      if (sscanf(argv[argc - 1], "%d", &versionNumber) != 1)
      {
          // If parsing fails, consider it as a local file path
          local_file_path = argv[argc - 1];
      }
      else
      {
        local_file_path = argv[argc - 2];
      }
    }
    else
    {
      local_file_path = "newFile";
    }

		return rfs_get(local_file_path, remote_file_path, versionNumber);

	}
  else if (strcmp(command, "RM") == 0)
	{
    // Remove command must have 3 arguments
    if (argc != 3)
    {
      printf("INVALID INPUT - See Below for Help\n\n");
      print_help();
      return -1;
    }

    char* remote_file_path = argv[2];

		return rfs_remove(remote_file_path);

	}
  else if (strcmp(command, "LS") == 0)
	{
    // LS command must have 3 arguments
    if (argc != 3)
    {
      printf("INVALID INPUT - See Below for Help\n\n");
      print_help();
      return -1;
    }

    char* remote_file_path = argv[2];

		return rfs_ls(remote_file_path);

	}
  else if (strcmp(command, "STOP") == 0)
	{
    // Stop command must have 2 arguments
    if (argc != 2)
    {
      printf("INVALID INPUT - See Below for Help\n\n");
      print_help();
      return -1;
    }
    rfs_stop();

  }
  else
  {
    printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
  }
}

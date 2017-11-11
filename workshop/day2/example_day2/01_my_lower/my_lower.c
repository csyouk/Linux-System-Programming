#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

pid_t pid;

int main(int argc, char **argv)
{
	pid_t pid_temp;	
	int i;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc != 2) {
		printf("[%d] usage: %s {string}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	/* Code here */

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


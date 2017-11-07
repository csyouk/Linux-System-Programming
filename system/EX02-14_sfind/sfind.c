#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

typedef void (*sighandler_t)(int);
pid_t pid;
pid_t pid_temp;	

void timeout(int signal)
{
	printf("[%d] timeout!\n", pid);

	/* Implement code */
}

int main(int argc, char **argv)
{
	int i;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	for(i=1; i<argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");

	if(argc != 4) {
		printf("[%d] usage: %s {directory} {string} {timeout}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	/* Implement code */

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


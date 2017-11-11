#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
pid_t pid;
pid_t pid_temp;

void timeout(int signal)
{
	/* Code here */
}

int main(int argc, char **argv)
{
	sighandler_t sig_ret;
	int i;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc != 3) {
		printf("[%d] usage: %s {timeout seconds} {sleep seconds}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	/* Code here */

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


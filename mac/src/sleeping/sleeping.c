#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid;
	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	for(;;) {
		printf("[%d] sleeping 1 second\n", pid);
		sleep(1);
	}

	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}


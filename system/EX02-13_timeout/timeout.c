#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

typedef void (*sighandler_t)(int);
pid_t pid;

void timeout(int signal)
{
	printf("[%d] timeout!\n", pid);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	sighandler_t sig_ret;
	int i;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	sig_ret = signal(SIGALRM, timeout);
	if(sig_ret == SIG_ERR) {
		printf("[%d] can't set signal handler\n", pid);
		return EXIT_FAILURE;
	}

	alarm(5);
	for(i=0; i<3; i++) {
		printf("[%d] do something %d\n", pid, i);
		sleep(1);
	}

	alarm(3);
	for(i=0; i<5; i++) {
		printf("[%d] do something %d\n", pid, i);
		sleep(1);
	}
	alarm(0);

	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}




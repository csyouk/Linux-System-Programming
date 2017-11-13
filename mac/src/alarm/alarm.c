#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

typedef void (*sighandler_t)(int);
pid_t pid;

void sigalrm_handler(int signal)
{
	printf("[%d] got signal %d\n", pid, signal);
}

int main(int argc, char **argv)
{
	sighandler_t sig_ret;
	unsigned int alarm_ret;
	int i;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	sig_ret = signal(SIGALRM, sigalrm_handler);
	if(sig_ret == SIG_ERR) {
		printf("[%d] can't set signal handler\n", pid);
		return EXIT_FAILURE;
	}

	alarm_ret = alarm(3);
	printf("[%d] alarm(3) returned %u\n", pid, alarm_ret);

	sleep(1);

	alarm_ret = alarm(4);
	printf("[%d] alarm(4) returned %u\n", pid, alarm_ret);
	
	printf("[%d] pause!!!\n", pid);
	pause();

	alarm_ret = alarm(5);
	printf("[%d] alarm(5) returned %u\n", pid, alarm_ret);

	alarm_ret = alarm(0);
	printf("[%d] alarm(0) returned %u\n", pid, alarm_ret);

	for(i=0; i<10; i++) {
		printf("[%d] %d seconds\n", pid, i);
		sleep(1);
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}




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

	pid_temp = fork();

	if(pid_temp == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	else if(pid_temp == 0) {
		int ret;
		pid = getpid();
		printf("[%d] changing process\n", pid);
		ret = execl("lower", "lower", argv[1], NULL);
		printf("[%d] ret = %#x (%#x)\n", pid, ret, WEXITSTATUS(ret));
	}
	else {
		pid_t pid_wait;
		int status;

		printf("[%d] waiting child's termination\n", pid);
		pid_wait = wait(&status);
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_wait, status);
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


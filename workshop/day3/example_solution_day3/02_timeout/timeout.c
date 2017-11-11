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
	printf("[%d] timeout!\n", pid);
	kill(pid_temp, SIGKILL);
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

	pid_temp = fork();

	if(pid_temp == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	else if(pid_temp == 0) {
		int ret;
		pid = getpid();
		printf("[%d] changing process\n", pid);
		ret = execl("/bin/sleep", "sleep", argv[2], NULL);
		printf("[%d] ret = %#x (%#x)\n", pid, ret, WEXITSTATUS(ret));
	}
	else {
		pid_t pid_wait;
		int status;

		sig_ret = signal(SIGALRM, timeout);
		if(sig_ret == SIG_ERR) {
			printf("[%d] can't set signal handler\n", pid);
				return EXIT_FAILURE;
		}
		alarm((unsigned int)(atoi(argv[1])));

		printf("[%d] waiting child's termination\n", pid);
		pid_wait = wait(&status);
		alarm(0);
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_wait, status);
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


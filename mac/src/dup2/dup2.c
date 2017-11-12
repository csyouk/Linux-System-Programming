#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 512

pid_t pid;

int main(int argc, char **argv)
{
	int fd_pipe[2];
	int ret;
	char wbuf[MAX_BUF];
	char rbuf[MAX_BUF];
	pid_t pid_temp;


	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* open pipe */ 
	ret = pipe(fd_pipe);
	if(ret == -1) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}

	pid_temp = fork();
	if(pid_temp == -1) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}
	else if(pid_temp == 0)
	{
		printf("[%d] child running\n", pid = getpid());


		/* 1: close fd 0 */
		close(1);
		/* 2: duplicate */
		dup(fd_pipe[1]);
		/* 3: close fd_pipe[0] */
		close(fd_pipe[1]);
		/* 4: close fd_pipe[1] */
		close(fd_pipe[0]);

		execlp("ls", "ls", "-al", NULL);
	}
	else {
		int status;
		int i;

		/* close fd_pipe[1] */
		close(fd_pipe[1]);

		/* read data from pipe */
		printf("[%d] reading from pipe\n", pid);
		for(;;) {
			ret = read(fd_pipe[0], rbuf, MAX_BUF-1);
			if(ret == -1) {
				printf("[%d] error: %s\n", pid, strerror(errno));
				return EXIT_FAILURE;
			}
			if(ret == 0) break;
			rbuf[ret] = 0;
			printf("%s", rbuf);
		}
		printf("[%d] end of reading\n", pid);

		/* close fd_pipe[0] */
		close(fd_pipe[0]);

		printf("[%d] waiting child's termination\n", pid);
		pid_temp = wait(&status);
		printf("\n");
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_temp, status);
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

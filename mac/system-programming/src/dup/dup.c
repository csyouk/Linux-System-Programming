#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 1024

pid_t pid;

int main(int argc, char **argv)
{
	int fd_pipe[2];
	int ret;
	char wbuf[MAX_BUF];
	char rbuf[MAX_BUF];
	pid_t pid_temp;


	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc < 2) {
		printf("[%d] usage: %s {str1} {str2} ...\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

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
		// 자식 프로세스
		printf("[%d] child running\n", pid = getpid());

		/* 1: close fd 0, stdin */
		close(0);
		/* 2: duplicate, set fd 0 as fd_pipe[0] (read) */
		dup(fd_pipe[0]);
		/* 3: close fd_pipe[0] */
		close(fd_pipe[0]);
		/* 4: close fd_pipe[1] */
		close(fd_pipe[1]);

		execlp("tr", "tr", "a-z", "A-Z", NULL);
	}
	else {
		// 부모 프로세스
		int status;
		int i;

		/* close fd_pipe[0] */
		close(fd_pipe[0]);

		/* write data to pipe */
		strcpy(wbuf, argv[1]);
		for(i=2; i<argc; i++) {
			strcat(wbuf, " ");
			strcat(wbuf, argv[i]);
		}
		ret = write(fd_pipe[1], wbuf, strlen(wbuf)+1);
		if(ret == -1) {
			printf("[%d] error: %s\n", pid, strerror(errno));
			return EXIT_FAILURE;
		}
		printf("[%d] wrote %d bytes to pipe [%s]\n", pid, ret, wbuf);

		/* close fd_pipe[1] */
		close(fd_pipe[1]);

		printf("[%d] waiting child's termination\n", pid);
		pid_temp = wait(&status);
		printf("\n");
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_temp, status);
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

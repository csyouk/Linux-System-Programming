#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 512
#define ERROR -1
#define CHILD 0
pid_t pid;

int main(int argc, char **argv)
{
	int fd_pipe[2];
	int ret;
	char wbuf[MAX_BUF];
	char rbuf[MAX_BUF];
	pid_t pid_temp;

	if(argc < 2){
		printf("usage : ./pipe_fork.c {ANY TEXT WORD}\n");
		return EXIT_FAILURE;
	}	


	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	
	/* open pipe */ 
	ret = pipe(fd_pipe);
	if(ret == ERROR) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}

	pid_temp = fork();
	if(pid_temp == ERROR) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}
	else if(pid_temp == CHILD) {
		printf("[%d] child running\n", pid = getpid());

		ret = read(fd_pipe[0], rbuf, MAX_BUF);
		if(ret == ERROR) {
			printf("[%d] error: %s\n", pid, strerror(errno));
			return EXIT_FAILURE;
		}
		printf("[%d] read %d bytes from pipe [%s]\n", pid, ret, rbuf);
	}
	else {
		int status;

		/* write data to pipe */
		strcpy(wbuf, argv[1]);
		ret = write(fd_pipe[1], wbuf, strlen(wbuf)+1);
		if(ret == ERROR) {
			printf("[%d] error: %s\n", pid, strerror(errno));
			return EXIT_FAILURE;
		}
		printf("[%d] wrote %d bytes to pipe [%s]\n", pid, ret, wbuf);

		printf("[%d] waiting child's termination\n", pid);
		pid_temp = wait(&status);
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_temp, status);
	}

	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}

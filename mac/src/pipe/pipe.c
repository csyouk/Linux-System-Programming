#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 512
#define ERROR -1
#define READ 0
#define WRITE 1
pid_t pid;

int main(int argc, char **argv)
{
	int fd_pipe[2];
	int ret;
	char wbuf[MAX_BUF];
	char rbuf[MAX_BUF];

	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc < 2){
		printf("usage : ./pipe {ANY TEXT WORD}\n");
		return EXIT_FAILURE;
	}
	/* open pipe */ 
	ret = pipe(fd_pipe);
	if(ret == ERROR) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}

	/* write data to pipe */
	strcpy(wbuf, argv[1]);
	ret = write(fd_pipe[WRITE], wbuf, strlen(wbuf)+1);
	if(ret == ERROR) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}
	printf("[%d] wrote %d bytes to pipe [%s]\n", pid, ret, wbuf);

	/* read data from pipe */
	ret = read(fd_pipe[READ], rbuf, MAX_BUF);
	if(ret == ERROR) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}
	printf("[%d] read %d bytes from pipe [%s]\n", pid, ret, rbuf);

	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}

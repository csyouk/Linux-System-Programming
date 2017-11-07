#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define MAX_BUF 512
#define PATH_FIFO "./my_fifo"

pid_t pid;

int main(int argc, char **argv)
{
	int fd_fifo;
	int ret;
	char wbuf[MAX_BUF];
	int i;


	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc < 2) {
		printf("[%d] usage: %s {str1} {str2} ...\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	/* make fifo */
	ret = mkfifo(PATH_FIFO, 0777);
	if(ret == -1) {
		if(errno == EEXIST) {
			printf("[%d] %s already exists\n", pid, PATH_FIFO);
		}
		else {
			printf("[%d] error: %s\n", pid, strerror(errno));
			return EXIT_FAILURE;
		}
	}

	/* open fifo */
	fd_fifo = open(PATH_FIFO, O_WRONLY);
	if(fd_fifo == -1) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}

	/* write data to pipe */
	strcpy(wbuf, argv[1]);
	for(i=2; i<argc; i++) {
		strcat(wbuf, " ");
		strcat(wbuf, argv[i]);
	}
	ret = write(fd_fifo, wbuf, strlen(wbuf)+1);
	if(ret == -1) {
		printf("[%d] error: %s\n", pid, strerror(errno));
		return EXIT_FAILURE;
	}
	printf("[%d] wrote %d bytes to %s [%s]\n", pid, ret, PATH_FIFO, wbuf);

	close(fd_fifo);

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

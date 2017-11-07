#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "msg.h"

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int id_msg;
	int i;
	struct msg_buf msgbuf;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	if(argc != 3) {
		printf("[%d] usage: %s {op1} {op2}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}
	printf(" %s %s\n", argv[1], argv[2]);

	/* Implement code */

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


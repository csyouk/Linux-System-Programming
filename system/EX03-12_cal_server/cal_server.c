#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msg.h"

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int id_msg;
	struct msg_buf msgbuf;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Implement code */

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


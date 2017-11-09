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

	id_msg = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
	if(id_msg == -1){
		printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	msgbuf.mtype = MTYPE_C2S;
	msgbuf.op1 = atoi(argv[1]);
	msgbuf.op2 = atoi(argv[2]);

	ret = msgsnd(id_msg, (void *)&msgbuf, sizeof(struct msg_buf)-sizeof(long), 0);
	if(ret == -1){
		printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}


	ret = msgrcv(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), MTYPE_S2C, 0);
	if(ret == -1){
		printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	printf("[%d] %d * %d = %d\n", pid, msgbuf.op1, msgbuf.op2, msgbuf.result);




	return EXIT_SUCCESS;
}


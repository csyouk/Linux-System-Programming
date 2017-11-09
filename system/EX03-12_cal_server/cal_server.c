#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "msg.h"
pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int msgq_id;
	struct msg_buf msgbuf;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Implement code */
	msgq_id = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
	if(msgq_id == -1){ 
	printf("Error create message Q with Key : %x\n", KEY_MSG);
	return EXIT_FAILURE;
	}

	while(1){
	ret = msgrcv(msgq_id, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), MTYPE_C2S, 0);
	if(ret == -1){
		printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	printf("[%d] %d * %d = %d\n", pid, msgbuf.op1, msgbuf.op2, msgbuf.op1*msgbuf.op2);

	msgbuf.result = msgbuf.op1 * msgbuf.op2;
	msgbuf.mtype = MTYPE_S2C;
	ret = msgsnd(msgq_id, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), 0);

	if(ret == -1){
	  printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}


	}


	printf("Terminated\n");


	return EXIT_SUCCESS;
}


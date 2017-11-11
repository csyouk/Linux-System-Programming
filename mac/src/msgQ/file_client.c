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
#include <sys/msg.h>

#include "msg.h"

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int id_msg;
	int i;
	struct msg_buf msgbuf;

	if(argc != 2) {
		printf("[%d] usage: %s {file name}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}
	printf("[%d] running %s", pid = getpid(), argv[0]);
	printf(" %s\n", argv[1]);

	if(strlen(argv[1]) >= MAX_FNAME) {
		printf("[%d] error: maximum file length is %d\n", pid, MAX_FNAME);
		return EXIT_FAILURE;
	}

	/* Code here */
	// get msgq
	id_msg = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
	if(id_msg == ERROR){
		printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	// initialize the msgbuf
	msgbuf.mtype = MTYPE_C2S;
	strcpy(msgbuf.fname, argv[1]);
	// printf("argument copied! : %s\n", msgbuf.fname);
	
	// sending msg to server
	ret = msgsnd(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), 0);
	if(ret == ERROR){
	  printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}	

	// wait msg from server
	ret = msgrcv(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), MTYPE_S2C, 0);
	if(ret == ERROR){
	  printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	// print msg from server
	if(msgbuf.valid){
		printf("[%d] %s:sizeof = %ld bytes, mode = %o\n", pid, argv[1], (long)msgbuf.size, msgbuf.mode);
	} else{
		printf("[%d] %s: invalid file\n", pid, msgbuf.fname);
	}



	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


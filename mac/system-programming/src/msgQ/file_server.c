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
	struct stat sb;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Code here */
	id_msg = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
	if(id_msg == ERROR){
	  printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	while(1){
		ret = msgrcv(id_msg, (void *)&msgbuf, sizeof(struct msg_buf)-sizeof(long), MTYPE_C2S, 0);
		if(ret == ERROR){
		  printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		printf("[%d] msg from client====\n", pid);
		printf("[%d] file name : %s\n", pid, msgbuf.fname);
		if(stat(msgbuf.fname, &sb) == ERROR){
			msgbuf.valid = 0;
		}else{
			msgbuf.valid = 1;
			msgbuf.size = sb.st_size;
			msgbuf.mode = sb.st_mode;

	 		printf("[%d] size : %lld, mode : %d, inode : %llu, dev : %d, hardlink : %d, uid : %d, gid : %d, blocksize: %lld\n ", pid, sb.st_size, sb.st_mode, sb.st_ino, sb.st_dev, sb.st_nlink, sb.st_uid, sb.st_gid, sb.st_blocks);
		}
		msgbuf.mtype = MTYPE_S2C;
		

		ret = msgsnd(id_msg, (void *)&msgbuf, sizeof(struct msg_buf)-sizeof(long), 0);
		if(ret == ERROR){
			printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


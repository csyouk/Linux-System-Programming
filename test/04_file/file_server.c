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
	struct stat st;
	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Code here */

	id_msg = msgget((key_t)KEY_MSG, 0666|IPC_CREAT);
	if(id_msg == -1) {
	  printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
	  return EXIT_FAILURE;
	}
	
	

	for(;;) {
	  ret = msgrcv(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), MTYPE_C2S, 0);
	  if(ret == -1) {
	    printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		  return EXIT_FAILURE;
		}
		if(ret > 0){
			if(stat(msgbuf.fname, &st) == -1){
				msgbuf.valid = 0;
			}else{
				msgbuf.valid = 1;
				msgbuf.size = st.st_size;
			}
		
			msgbuf.mtype = MTYPE_S2C;
		}

		ret = msgsnd(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), 0);
		if(ret == -1) {
	  	printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
	  	return EXIT_FAILURE;
		}

		//waiting mode msg
		if((msgbuf.valid) && (st.st_size > 1024)){
			printf("when size is over than 1kB %d\n", st.st_size);
		  ret = msgrcv(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), MTYPE_C2S_MODE, 0);
		  if(ret == -1) {
		    printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			  return EXIT_FAILURE;
			}
			if(ret > 0){
				if(stat(msgbuf.fname, &st) == -1){
					msgbuf.valid = 0;
				}else{
					msgbuf.valid = 1;
					msgbuf.size = st.st_mode;
				}
		
				msgbuf.mtype = MTYPE_S2C_MODE;
			}

			ret = msgsnd(id_msg, (void *)&msgbuf, sizeof(struct msg_buf) - sizeof(long), 0);
			if(ret == -1) {
		  	printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		  	return EXIT_FAILURE;
			}

		}
	
	}
	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


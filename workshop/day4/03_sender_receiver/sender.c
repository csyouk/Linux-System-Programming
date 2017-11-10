#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>

#include "sem.h"
#include "shm.h"

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int id_shm;
	struct shdata *shmbuf;
	int data;
	int id_sem;
	struct sembuf sb;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Code here */
	id_sem = semget((key_t)KEY_SEM, 1, 0666|IPC_CREAT);
	if(id_sem == ERROR){
		printf("[%d] error %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	id_shm = shmget(KEY_SHM, sizeof(struct shdata), 0666|IPC_CREAT);
	if(id_shm == ERROR){
		printf("[%d] error %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	shmbuf = (struct shdata *)shmat(id_shm, (void *)0, 0);
	if(shmbuf == (struct shdata *)ERROR){
		printf("[%d] error %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	//init values
	shmbuf->written = READ;
	shmbuf->data = 1;
	data = 1;
	while(1){
		//read
		if(shmbuf->written == READ){
				ret = semop(id_sem, &sb, 1);
				if(ret == ERROR){
					printf("[%d] error %s(%d)\n", pid, strerror(errno), __LINE__);
					return EXIT_FAILURE;
				}
				shmbuf->data = data++;
				shmbuf->written = WRITE;
				if(data == 101){ break; }
				ret = semop(id_sem,&sb,1);
				if(ret == ERROR){
					printf("[%d] error %s(%d)\n", pid, strerror(errno), __LINE__);
					return EXIT_FAILURE;
				}
		}
	}


	ret = shmdt(shmbuf);
	if(ret == ERROR){
		printf("[%d] error %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}


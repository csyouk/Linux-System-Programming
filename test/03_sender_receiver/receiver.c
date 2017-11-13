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

#include "shm.h"
#include "sem.h"
#define ERROR -1
pid_t pid;

int main(int argc, char **argv)
{
	int i;
	int ret;
	int id_shm;
	struct shdata *shm_buf;
	int sem_id;
	struct sembuf sb;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Code here */
		// get semephore
	sem_id = semget((key_t)KEY_SEM, 1, 0666|IPC_CREAT);
	if(sem_id == ERROR){
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	// get shared mem
	id_shm = shmget((key_t)KEY_SHM, sizeof(struct shdata), 0666|IPC_CREAT);
	if(id_shm == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	// attach shared mem
	shm_buf = shmat(id_shm, (void *)0, 0);
	if(shm_buf == (struct shdata *)-1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	// R&W 100 times
	for(i=1;i<=100;){	
		sb.sem_num = 0;
		sb.sem_op = -1;
		sb.sem_flg = SEM_UNDO;

		// read and write
		// enter critical area
		ret = semop(sem_id, &sb, 1);
		if(ret == ERROR){
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		if(shm_buf->sent == 1){
			printf("%s\n",shm_buf->data);
			shm_buf->sent = 0;
			i++;
		}

		sb.sem_num = 0;
		sb.sem_op = 1;
		sb.sem_flg = SEM_UNDO;
		ret = semop(sem_id, &sb, 1);
		if(ret == ERROR){
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		// end critical area
	}


	// detach shared mem

	ret = shmdt(shm_buf);
	if(ret == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}


	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}


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

pid_t pid;

int main(int argc, char **argv)
{
	int i;
	int ret;
	int id_shm;
	struct shdata *shmbuf;
	int id_sem;
	struct sembuf sb;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	id_sem = semget((key_t)KEY_SEM, 1, 0666|IPC_CREAT);
	if(id_sem == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	id_shm = shmget((key_t)KEY_SHM, sizeof(struct shdata), 0666|IPC_CREAT);
	if(id_shm == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	shmbuf = shmat(id_shm, (void *)0, 0);
	if(shmbuf == (struct shdata *)-1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}

	for(i=0; i<100;) {
		sb.sem_num = 0;
		sb.sem_op = -1;
		sb.sem_flg = SEM_UNDO;
		ret = semop(id_sem, &sb, 1);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		if(shmbuf->written == 1) {
			printf("%d\n", shmbuf->data);
			shmbuf->written = 0;
			i++;
		}

		sb.sem_num = 0;
		sb.sem_op = 1;
		sb.sem_flg = SEM_UNDO;
		ret = semop(id_sem, &sb, 1);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

	}

	ret = shmdt(shmbuf);
	if(ret == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}


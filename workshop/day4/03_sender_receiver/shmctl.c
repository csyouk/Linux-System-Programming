#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shm.h"

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int id_shm;
	struct shdata *shmbuf;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc != 2) {
		printf("[%d] usage: %s {command}\n", pid, argv[0]);
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
	
	if(strcmp(argv[1], "IPC_RMID") == 0) {
		ret = shmctl(id_shm, IPC_RMID, 0);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		printf("[%d] IPC_RMID OK\n", pid);
	}

	ret = shmdt(shmbuf);
	if(ret == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}

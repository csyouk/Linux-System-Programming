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
	int i;
	int id_sem;
	struct sembuf sb;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	/* Code here */
	
	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}


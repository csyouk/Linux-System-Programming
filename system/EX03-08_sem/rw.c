#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "sem.h"

#define FILE_TEST "./test.txt"
#define LOOP_COUNT 50

pid_t pid;

int main(int argc, char **argv)
{
	int ret;
	int i;
	char c1 = 'A';
	char c2;
	int fd;
	int id_sem;
	struct sembuf sb;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

	id_sem = semget((key_t)KEY_SEM, 1, 0666|IPC_CREAT);
	if(id_sem == -1) {
		printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	
	for(i=0; i<LOOP_COUNT; i++) {
		printf("[%d] LOOP %d\n", pid, i);

		sb.sem_num = 0;
		sb.sem_op = -1;
		sb.sem_flg = SEM_UNDO;
		ret = semop(id_sem, &sb, 1);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		fd = open(FILE_TEST, O_RDWR|O_CREAT, 0777);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		ret = write(fd, &c1, sizeof(char));
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		ret = close(fd);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		usleep(rand()%500000);

		fd = open(FILE_TEST, O_RDWR);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		ret = read(fd, &c2, sizeof(char));
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		ret = close(fd);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		if(c1 != c2) {
			printf("[%d] error: not same (%d)\n", pid,  __LINE__);
			return EXIT_FAILURE;
		}
		sb.sem_num = 0;
		sb.sem_op = 1;
		sb.sem_flg = SEM_UNDO;
		ret = semop(id_sem, &sb, 1);
		if(ret == -1) {
			printf("[%d] error: %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}

		c1++;
	}

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

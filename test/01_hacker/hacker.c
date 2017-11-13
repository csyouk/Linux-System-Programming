#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define ERROR -1
#define CHILD 0

pid_t pid;

int main(int argc, char **argv)
{
	pid_t pid_temp;	
	int i;
	int ret;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc != 2) {
		printf("[%d] usage: %s {string}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	if(argc < 1){
		printf("[%d] usage : %s {str1}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	/* Code here */
	pid_temp = fork();
	if(pid_temp == ERROR){
		printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	else if(pid_temp == CHILD){
		// child process
		ret = execl("./passfree", "passfree", argv[1], NULL);
		if(ret == ERROR){
			printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
	}else{
		int status;
		pid_t wait_pid;

		printf("[%d] waiting for child process termination\n", pid);
		wait_pid = waitpid(pid_temp, &status, 0);
		printf("[%d] child process endded. with status.%d\n", pid, status);  
	}



	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


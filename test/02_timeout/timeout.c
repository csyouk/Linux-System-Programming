#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define ERROR -1
#define CHILD 0

typedef void (*sighandler_t)(int);
pid_t pid;
pid_t pid_temp;

void timeout(int signal)
{
	printf("[%d] timeout!\n", pid);

	/* Code here */
	kill(pid_temp, SIGKILL);
}

int main(int argc, char **argv)
{
	sighandler_t sig_ret;
	int i;
	int ret;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	if(argc != 3) {
		printf("[%d] usage: %s {timeout seconds} {program}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}
	printf(" %s %s\n", argv[1], argv[2]);

	/* Code here */
	sig_ret = signal(SIGALRM, timeout);
	if(sig_ret == SIG_ERR){
		printf("[%d] can't set signal handler\n", pid);
		return EXIT_FAILURE;	
	}


	pid_temp = fork();
	if(pid_temp == ERROR){
		printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}else if(pid_temp == CHILD){
		
		ret = execl(argv[2], argv[2], NULL);
		if(ret == ERROR){
			printf("[%d] error : %s(%d)\n", pid, strerror(errno), __LINE__);
			exit(-15);
		}
	}else{
		// this is parent process.
		int status;
		pid_t wait_pid;	
		alarm(atoi(argv[1]));
		
		wait_pid = wait(&status);
		printf("==================================================\n");
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_temp, status);
		printf("==================================================\n");
		alarm(0);	
	}



	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


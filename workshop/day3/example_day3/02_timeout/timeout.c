#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
pid_t pid;
pid_t pid_temp;

void timeout(int signal)
{
	/* Code here */
	printf("[%d] Child proccess is about to kill.\n", pid_temp);
  kill(pid_temp, SIGKILL);
}

int main(int argc, char **argv)
{
	sighandler_t sig_ret;
	int i;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);
	if(argc != 3) {
		printf("[%d] usage: %s {timeout seconds} {sleep seconds}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

	/* Code here */
	pid_temp = fork();
	if(pid_temp == -1){
		printf("[%d] error create child process %s %d\n", pid, strerror(errno), __LINE__);
		return EXIT_FAILURE;
	} else if(pid_temp == 0){
		printf("[%d] child process.\n", getpid());
		sleep(atoi(argv[2]));
		printf("[%d] Child proccess died\n", getpid());
	}else{
		int status;
		pid_t pid_wait;
		printf("[%d] parent process.\n", pid);
		
		sig_ret = signal(SIGALRM, timeout);
		sleep(atoi(argv[1]));
		alarm(3);	
		pid_wait = wait(&status);
		printf("[%d] Parent Proccess status : %d\n", pid, status);
		

		alarm(0);
		
	}



	return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

typedef void (*sighandler_t)(int);
pid_t pid;
pid_t pid_temp;	

void timeout(int signal)
{
	printf("[%d] timeout!\n", pid);

	/* Implement code */
	//int result = kill(pid, SIGKILL);
	//printf("kill result : %d\n", result);

	kill(pid_temp, SIGKILL);
}

int main(int argc, char **argv)
{
	int i;
	sighandler_t sig_ret;
	printf("[%d] running %s", pid = getpid(), argv[0]);
	for(i=1; i<argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");

	if(argc != 4) {
		printf("[%d] usage: %s {directory} {string} {timeout}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}

  printf("argc : %d\n", argc);	
	printf("sec : %d\n", atoi(argv[3]));

	/*  set handler*/
	sig_ret = signal(SIGALRM, timeout);
	if(sig_ret == SIG_ERR) {
		printf("[%d] can't set signal handler\n", pid);
		return EXIT_FAILURE;
	}

	/* Implement code */
		pid_temp = fork();
		if(pid_temp == -1){
			printf("[%d] error %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		else if(pid_temp == 0){
			pid = getpid();
			// kill child proces by itself
			//alarm(atoi(argv[3]));
      printf("Child [%d] about to run [grep -rn %s %s]\n", pid, argv[2], argv[1]);
			execlp("grep", "grep", "-rn", argv[2], argv[1],  NULL);
			printf("Child [%d] has been forked\n", pid);
		}

		alarm((unsigned int)(atoi(argv[3])));

		int status;
		int pid_wait = wait(&status);
		printf("[%d] pid %d has been terminated with status  %d\n",pid,  pid_wait, status);


	printf("[%d] terminated\n", pid);

	return EXIT_SUCCESS;
}


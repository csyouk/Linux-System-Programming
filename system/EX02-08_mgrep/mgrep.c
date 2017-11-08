#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

pid_t pid;

int main(int argc, char **argv)
{
	pid_t pid_temp;
	int i;
	int num_of_child;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	for(i=1; i<argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");

	num_of_child = argc - 2;

	/* Implement code */
	/* Implement code */
	for(i=0; i < num_of_child;i++){
		pid_temp = fork();
		if(pid_temp == 0){
			printf("about to run [grep -rn %s /etc]\n", argv[2+i]);
			execlp("grep", "grep", "-rn", argv[2+i], "/etc", NULL);
		} else {
			int status;
			pid_wait = wait(&status);
			printf("pid [%d] has been terminted with status %d\n", pid_wait, status);
		}
	}
	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}

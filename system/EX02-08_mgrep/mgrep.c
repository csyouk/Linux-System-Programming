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
	for(i=0; i < num_of_child;i++){
		pid_temp = fork();
		if(pid_temp == -1){
			printf("[%d] error : %s (%d)\n", pid, strerror(errno), __LINE__);
			return EXIT_FAILURE;
		}
		else if(pid_temp == 0){
			printf("about to run [grep -rn %s /etc]\n", argv[2+i]);
			execlp("grep", "grep", "-rn", argv[2+i], argv[1], NULL);
			printf("=============="); // exec가 제대로 프로세스를 교체했다면, 이 실행문은 실행되지 않는다.
		}
	}

	for(i=0; i < num_of_child; i++){
		int status;
		printf("[%d] waiting child's termination\n", pid);
		pid_wait = wait(&status);
		printf("[%d] pid %d has been terminated with status %#x\n", pid, pid_wait, status);
	}

	printf("[%d] terminated\n", pid);


	return EXIT_SUCCESS;
}

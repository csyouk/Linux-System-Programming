#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t pid;

int main(int argc, char **argv)
{
	int i, ret;

	printf("[%d] running %s\n", pid = getpid(), argv[0]);

#if 1
	ret = execl("/bin/ls", "ls", "-l", NULL);
#endif

#if 0
	ret = execl("ls", "ls", "-l", NULL);
#endif

#if 0
	ret = execlp("ls", "ls", "-l", NULL);
#endif

	printf("[%d] ret = %d\n", pid, ret);

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}


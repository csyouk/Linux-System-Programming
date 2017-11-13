#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	int ret;
	
	printf("command = ls -l\n");
	ret = system("ls -l");
	printf("-> ret = %#x (%#x)\n", ret, WEXITSTATUS(ret));

	printf("command = wrong command\n");
	ret = system("wrong command");
	printf("-> ret = %#x (%#x)\n", ret, WEXITSTATUS(ret));

	printf("command = sleep 3\n");
	ret = system("sleep 3");
	printf("-> ret = %#x (%#x)\n", ret, WEXITSTATUS(ret));

	printf("command = sleep 3 &\n");
	ret = system("sleep 3 &");
	printf("-> ret = %#x (%#x)\n", ret, WEXITSTATUS(ret));

	printf("command = ./dup2\n");
	ret = system("./dup2");
	printf("->ret = %#x (%#x)\n", ret, WEXITSTATUS(ret));

	return EXIT_SUCCESS;
}


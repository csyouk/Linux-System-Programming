#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t pid;

int main(int argc, char **argv)
{
	int i;
	char *s;

	printf("[%d] running %s", pid = getpid(), argv[0]);
	if(argc != 2) {
		printf("[%d] usage: %s {string}\n", pid, argv[0]);
		return EXIT_FAILURE;
	}
	printf(" %s\n", argv[1]);

	s = argv[1];

	while(*s) {
		if((*s >= 'A') && (*s <='Z')) {
			*s = *s + ('a' - 'A');
		}
		s++;
	}

	printf("==========================\n");
	printf("result is %s\n", argv[1]);		
	printf("==========================\n");

	printf("[%d] terminted\n", pid);

	return EXIT_SUCCESS;
}	

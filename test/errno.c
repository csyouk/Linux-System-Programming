#include <stdio.h>
#include <errno.h>
int main(int argc, char **argv){
	printf("%d\n", __LINE__);
	printf("%d\n", strerror(errno));
	return 0;
}
// output
// 4
// 690112, 매번 바뀜.

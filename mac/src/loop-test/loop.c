#include <stdio.h>
#define ULL unsigned long long int

int main(int argc, char **argv){
	ULL i;
	ULL sum=0;
	ULL max = 10000000000;
	for(i=0; i<max; i++){
		sum += i;
	}

	printf("sum : %llu\n", sum);


	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ULL unsigned long long int
#define UNIT 100000000


void * worker(void *arg){
	//printf("arg : %d\n", *(int*)arg);
	ULL i;
	ULL sum=0;
	int b = *(int *)arg;
	for(i=b*UNIT; i<(b+1)*UNIT; i++){
		sum += i;
	}
	pthread_exit((void*)sum);
}

int main(int argc, char **argv){
	pthread_t threads[10];
	void * rets[10];
	ULL sum = 0;
	int i;
	int id[10];

	for(i=0; i<10; i++){
		id[i] = i;
		if(pthread_create(threads + i, NULL, worker,  (void *)(id + i)) != 0){
			printf("error making thread %d\n", i);
		}
	}
	for(i=0; i<10; i++){
		if(pthread_join(threads[i], &rets[i]) != 0){
			printf("error join thread %d\n", i);
		}
	}

	for(i=0; i<10; i++){
		sum += *(ULL*)(rets + i);
	}

	printf("sum : %llu\n", sum);


	return 0;
}

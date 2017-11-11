#define KEY_SEM 0xf8f8

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short * array;
	struct seminfo *__buf;
};

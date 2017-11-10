#define KEY_SHM 0x2222

#define STATUS_UNKNOWN 0
#define STATUS_RUNNING 1
#define STATUS_EXIT 2

#define TIMEOUT 30
#define ERROR -1
#define WRITE 1
#define READ 0
struct shdata {
	/* Code here */
	int written;
	char data;
};


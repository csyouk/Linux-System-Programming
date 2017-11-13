#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define KEY_MSG 0x3333
#define MAX_FNAME 64
#define ERROR -1

#define MTYPE_S2C 1 /* Server -> Client */
#define MTYPE_C2S 2 /* Client -> Server */

struct msg_buf {
	/* Code here */
	long mtype;
	char fname[MAX_FNAME];
	off_t size;
	mode_t mode;
	int valid;
};


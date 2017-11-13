#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define KEY_MSG 0x3333
#define MAX_FNAME 64

#define MTYPE_ALL 0 /* receive all mtypes */

#define MTYPE_S2C 1 /* Server -> Client for size */
#define MTYPE_C2S 2 /* Client -> Server for size */

#define MTYPE_S2C_MODE 3 /* Server -> Client for mode */
#define MTYPE_C2S_MODE 4 /* Client -> Server for mode */

struct msg_buf {
	long mtype;
	char fname[MAX_FNAME];
	off_t size;
	mode_t mode;
	int valid;
};


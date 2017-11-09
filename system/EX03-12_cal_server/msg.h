#define KEY_MSG 0xf8f8

#define MTYPE_S2C 1 /* Server -> Client */
#define MTYPE_C2S 2 /* Client -> Server */

struct msg_buf {
	long mtype;
	int op1;
	int op2;
	int result;
};


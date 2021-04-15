#ifndef	__KEY_BUFFER__
#define	__KEY_BUFFER__

#ifndef	TRUE
	#define TRUE 1
#endif	// TRUE

#ifndef	FALSE
	#define FALSE 0
#endif	//	FALSE

#define BUFFER_SIZE 64

typedef struct {
	int size;
	int buffer[BUFFER_SIZE];
	int in, out;
} KeyBuffer;

void InitKeyBuffer(KeyBuffer *buffer);
int IsEmpty(KeyBuffer *buffer);
int IsFull(KeyBuffer *buffer);
void InsertKey(KeyBuffer *buffer, int key);
int DeleteKey(KeyBuffer *buffer);
int GetKey(KeyBuffer *buffer, int idx);
void DisplayKeyBuffer(int x, int y, KeyBuffer *buffer);

#endif	//	__KEY_BUFFER__

#include <stdio.h>

#include "Console.h"
#include "KeyBuffer.h"

#define TRUE 1
#define FALSE 0

void InitKeyBuffer(KeyBuffer *buffer)
{
	buffer->in = buffer->out = 0;
	buffer->size = BUFFER_SIZE;
}

int IsEmpty(KeyBuffer *buffer)
{
	int result;
	result = buffer->in % buffer->size == buffer->out% buffer->size ? 1 : 0;
	return result;
}

int IsFull(KeyBuffer *buffer)
{
	int result;

	result = (buffer->in+1)%buffer->size== buffer->out%buffer->size ? 1 : 0;
	return result;
}


void InsertKey(KeyBuffer *buffer, int key)
{
	// TO DO: implement this function
	// if the buffer is full, do nothing
	if (!IsFull(buffer))
	{
		buffer->buffer[buffer->in] = key;
		buffer->in = (buffer->in+1) % buffer->size;
	}
}

int DeleteKey(KeyBuffer *buffer)
{
	// TO DO: implement this function
	// if the buffer is empty, do nothing
	if (!IsEmpty(buffer))
	{
		int result;
		result = buffer->buffer[buffer->out%buffer->size];
		buffer->out = (buffer->out+1) % buffer->size;
		return result;
	}
	return 0;
}

int GetKey(KeyBuffer *buffer, int idx)
{
	return buffer->buffer[idx];
}

void DisplayKeyBuffer(int x, int y, KeyBuffer *buffer)
{
	gotoxy(x, y);

	printf("Key Buffer = [");
	for (int i = buffer->out; i != buffer->in; i = (i + 1) % buffer->size)
		printf("%c", GetKey(buffer, i));

	printf("] ");
}

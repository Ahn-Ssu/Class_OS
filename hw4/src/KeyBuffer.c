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
	// TO DO: implement this function
}

int IsFull(KeyBuffer *buffer)
{
	// TO DO: implement this function
}

void InsertKey(KeyBuffer *buffer, int key)
{
	// TO DO: implement this function
	// if the buffer is full, do nothing
}

int DeleteKey(KeyBuffer *buffer)
{
	// TO DO: implement this function
	// if the buffer is empty, do nothing
}

int GetKey(KeyBuffer *buffer, int idx)
{
	return buffer->buffer[idx];
}


void DisplayKeyBuffer(int x, int y, KeyBuffer *buffer)
{
	gotoxy(x, y);

	printf("Key Buffer = [");
	for(int i = buffer->out; i != buffer->in; i = (i + 1) % buffer->size)
		printf("%c", GetKey(buffer, i));

	printf("] ");
}


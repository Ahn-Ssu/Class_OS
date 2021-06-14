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
	// 버퍼가 circular니까 사이즈로 나눠줌
	// size보다 index가 -1 작음
	result = buffer->in == buffer->out ? 1 : 0;
	return result;
}

int IsFull(KeyBuffer *buffer)
{
	int result;
	// circular Queue에서, in의 나머지가 out보다 하나차이일 때 Q full
	result = (buffer->in+ 1)== buffer->out ? 1 : 0;
	return result;
}

void displayE(KeyBuffer *buffer){
	printf("\n\n\nin %d\n", buffer->in);
	printf("out %d\n", buffer->out);
	printf("size %d\n", buffer->size);
	printf("now is full?? %d\n", IsFull(buffer));
	printf("now is empty?? %d\n", IsEmpty(buffer));
}

void InsertKey(KeyBuffer *buffer, int key)
{
	// TO DO: implement this function
	// if the buffer is full, do nothing
	if (!IsFull(buffer))
	{
		// 버퍼가 가지고 있는 공간에, in번째 위치에 추가하고 증가
		buffer->buffer[buffer->in%buffer->size] = key;
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
		// 버퍼 구조체가 가지고 있는 공간에서, out에 위치한 key를 뽑고, out증가
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

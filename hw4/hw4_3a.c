#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"

int main(int argc, char *argv[])
{
	// TO DO: open SHM_FILE for using shm_open()
	int shm_fd;

	shm_fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);
	if (shm_fd == -1)
	{ //	check if the file was successfully open
		perror("shm_open");
		exit(0);
	}
	// errExit("shm_open");

	int buffer_size = sizeof(KeyBuffer);

	// TO DO: set size of the shared memory by buffer_size
	if (ftruncate(shm_fd, buffer_size) == -1)
	{
		perror("ftruncate");
		exit(0);
	}
	// errExit("ftruncate");

	KeyBuffer *key_buffer = NULL;
	// TO DO: map the shared memory file and receive the return address into key_buffer
	//	check if the file was successfully mapped
	key_buffer = mmap(0, buffer_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (key_buffer == MAP_FAILED)
	{
		perror("mmap");
		exit(0);
	}
	// errExit("mmap");

	// TO DO: initialize the key buffer in the shared memory
	InitKeyBuffer(key_buffer);

	clrscr();

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit hw4_3b, ESC: quit both\n");

	while (1)
	{
		gotoxy(1, 2);
		printf("Input a key: ");
		int key = getch();

		if (key == 27)
		{
			InsertKey(key_buffer, 'q');
			break;
		}
		else
		{
			InsertKey(key_buffer, key);
		}
		DisplayKeyBuffer(1, 2, key_buffer);
	}

	// TO DO: unmap and unlink the shared memory block

	if (munmap(shm_fd, buffer_size) == -1)
	{
		perror("munmap");
		exit(0);
	}
	// errExit("munmap");

	if (shm_unlink(SHM_FILE) == -1)
	{
		perror("shm_unlink");
		exit(0);
	}
	// errExit("shm_unlink");

	clrscr();
	printf("Bye!\n");

	return 0;
}

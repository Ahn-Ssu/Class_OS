#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv[])
{
	// TO DO: open SHM_FILE for using shm_open()
	//	check if the file was successfully open

	int buffer_size = sizeof(KeyBuffer);

	// TO DO: set size of the shared memory by buffer_size

	KeyBuffer *key_buffer = NULL;
	// TO DO: map the shared memory file and receive the return address into key_buffer
	//	check if the file was successfully mapped

	// TO DO: initialize the key buffer in the shared memory

	clrscr();

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit hw4_3b, ESC: quit both\n");

	while(1){
		gotoxy(1, 2);
		printf("Input a key: ");
		int key = getch();

		/* TO DO: implement the following action
			if key is ESC (ASCII 27), insert 'q' into the key buffer and break the loop
			otherwise, insert the key into the key buffer.

		*/

		DisplayKeyBuffer(1, 2, key_buffer);
	}

	// TO DO: unmap and unlink the shared memory block

	clrscr();
	printf("Bye!\n");

	return 0;
}


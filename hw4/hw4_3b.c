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


int main(int argc, char *argv)
{
	// TO DO: open SHM_FILE for using shm_open()
	//  check if the file was successfully open
	int shm_fd;

	shm_fd = shm_open(SHM_FILE, O_RDWR, 0666);
	if ( shm_fd == -1){
	       perror("shm_open");
       exit(0);
	} //      errExit("shm_open");


	int buffer_size = sizeof(KeyBuffer);

	// TO DO: map the shared memory file and receive the return address into key_buffer
	// check if the file was successfully mapped
	KeyBuffer *keybuffer = mmap(0, buffer_size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (keybuffer == MAP_FAILED){
			perror("mmap");
			exit(0);}
	//	errExit("mmap");
	// ?? mmap이 뭘 리턴하는가..
	
	if( keybuffer == NULL) printf("NULL");

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();

	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;
	int y = screen_height / 2;
	int key = 0;
	char c = '*';
	int repeat = 1;

	gotoxy(x, y);
	putchar('#');

	while(repeat){
		int oldx = x;
		int oldy = y;
		
		// TO DO: read a key from the key buffer in the shared memory
		// if the key is zero, repeat until a non-zero key is read
		while(TRUE){
			key = DeleteKey(keybuffer);
			if (key != 0) break;
		}


/*
		TO DO: implement the following actions

		if key is 'i', 'j', 'k', or 'l', move the coordinate accordingly
			'i': move up
			'j': move left
			'k': move down
			'l': move right

			Note! The coordinate should be in the valid range.
			(1 <= x <= screen_width, 1 <= y <= screen_height)

		if key is 'c', change color
			toggle c between ' ' and '*' 

		if key is 'q', break the loop
			
*/


		// TO DO: print c at (oldx, oldy)

		// TO DO: print '#' at (x, y)
		// (1 <= x <= screen_width, 1 <= y <= screen_height)
		if(key =='i') 1<y? y--: y; // 'i': move up
		if(key =='j') 1<x? x--: x; // 'j': move left
		if(key =='k') y<screen_height? y++:y; // 'k': move down
		if(key =='l') x<screen_width? x++: x; // 'l': move right

		if(key =='c')c = c=='*'?' ':'*'; // toggle c between ' ' and '*' 
		

		// TO DO: print c at (oldx, oldy)
		DrawLine(oldx, oldy, x,y, c);
		// TO DO: print '#' at (x, y)
		gotoxy(x, y);
		putchar('#'); // putchar는 좌표에 찍힘
	}

	clrscr();
	printf("Bye!\n");

	return 0;
}

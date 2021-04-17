#include <stdio.h>

#include "Console.h"

int main(int argc, char *argv[])
{
	clrscr();			// clear screen

	// retrieve the size of window
	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight()-3; 

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit\n");
	printf("screen size: %d x %d\n", screen_width, screen_height);

	int x = screen_width / 2;	// horizontal coordinate
	int y = screen_height / 2;	// vertical coordinate
	int key = 0;
	int repeat = 1;
	char c = '*';		// initial color

	gotoxy(x, y);		// move the cursor to (x, y)
	putchar('#');

	int oldx = 0, oldy = 0;
	while(repeat){
		// TO DO: save current coordinate in (oldx, oldy) 

		oldx = x; oldy =y;

		gotoxy(1, 3);
		printf("x = %3d, y = %3d", x, y);

		gotoxy(screen_width, 1);	// move cursor to upper right corner
		key = getch();		// read a key not waiting for ENTER


		// (1 <= x <= screen_width, 1 <= y <= screen_height)
		if(key =='i') 1<y? y--: y; // 'i': move up
		if(key =='j') 1<x? x--: x; // 'j': move left
		if(key =='k') y<screen_height? y++:y; // 'k': move down
		if(key =='l') x<screen_width? x++: x; // 'l': move right

		if(key =='c')c = c=='*'?' ':'*'; // toggle c between ' ' and '*' 
		
		if(key =='q')break; //if key is 'q', break the loop

		// TO DO: print c at (oldx, oldy)
		DrawLine(oldx, oldy, x,y, c);
		// TO DO: print '#' at (x, y)
		gotoxy(x, y);
		putchar('#'); 
	}

	clrscr();
	printf("Bye!\n");

	return 0;
}


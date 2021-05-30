/*
	Console.h: declarations for console-related functions
*/

#ifndef	__CONSOL__
#define	__CONSOL__

void clrscr(void);              // clear screen
void gotoxy(int x, int y);     // move cursor to (x, y) coordinate

int getWindowWidth();       // get width of current console window
int getWindowHeight();      // get width of current console window

void DrawLine(int x1, int y1, int x2, int y2, char c);
void swap(int *pa, int *pb);

void EnableCursor(int enable);
void PrintXY(int x, int y, const char *format, ...);

void MySleep(int msec);
void MyPause();

int kbhit();
int getch();

#endif	//	__CONSOL__


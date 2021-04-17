/*
	Console.c: console-related functions
		This file is for Linux.
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "Console.h"

void gotoxy(int x, int y)
{
	/*
		C/C++은 API나 MFC(?)를 사용핮 ㅣ않는 이상 GUI 사용이 불가능
		모든 것이 문자로 표현되기 때문에  콘솔창 내부에서 어디든지 자신의 좌표를 가지고 있음 
		gotoxy는 해당 좌표를 옮겨주는 함수! 
	*/
	printf("%c[%d;%df", 0x1B, y, x);
}

void clrscr()
{
	fprintf(stdout, "\033[2J\033[0;0f");
	fflush(stdout);
}

int getWindowWidth()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_col;
}

int getWindowHeight()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_row;
}

int getch()
{
	int c = 0;
	struct termios oldattr, newattr;

	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	newattr.c_cc[VMIN] = 1;
	newattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

	return c;
}

int kbhit(void)
{
	struct termios oldt, newt;
	int ch = 0;
	int oldf = 0;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getch();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

void EnableCursor(int enable)
{
	if (enable)
	{
		printf("\e[?25h");
		fflush(stdout);
	}
	else
	{
		printf("\e[?25l");
		fflush(stdout);
	}
}

void MySleep(int msec)
{
	usleep(msec * 1000);
}

void MyPause()
{
	printf("Press Enter to continue...");
	getchar();
}

void DrawLine(int x1, int y1, int x2, int y2, char c)
{
	int dx = 0, dy = 0;
	int x = 0, y = 0;

	if (abs(x2 - x1) > abs(y2 - y1))
	{
		if (x1 > x2)
		{
			swap(&x1, &x2);
			swap(&y1, &y2);
		}
	}
	else if (y1 > y2)
	{
		swap(&x1, &x2);
		swap(&y1, &y2);
	}

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx >= dy)
	{
		if (dx == 0)
		{
			gotoxy(x1, y1);
			printf("%c", c);
		}
		else
		{
			for (x = x1; x <= x2; x++)
			{
				y = (y1 * (x2 - x) + y2 * (x - x1) + dx / 2) / dx;
				gotoxy(x, y);
				printf("%c", c);
			}
		}
	}
	else
	{
		for (y = y1; y <= y2; y++)
		{
			x = (x1 * (y2 - y) + x2 * (y - y1) + dy / 2) / dy;
			gotoxy(x, y);
			printf("%c", c);
		}
	}
}

void swap(int *pa, int *pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

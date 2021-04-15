#include <stdio.h>

#include "Console.h"
#include "KeyBuffer.h"

int main(int argc, char *argv[])
{
	KeyBuffer key_buffer;
	InitKeyBuffer(&key_buffer);

	clrscr();
	while(1){
		gotoxy(1, 1);
		printf("Input a key (SPACE: delete a key, ESC: quit.): ");
		int key = getch();

		if(key == 27){			// ESC
			break;
		} else if(key == ' '){
			key = DeleteKey(&key_buffer);
			gotoxy(1, 3);
			if(key > 0){
				printf("key \'%c\' was deleted     \n", key);
			} else {
				printf("The key buffer is emtpy!\n");
			}
		} else {
			InsertKey(&key_buffer, key);
		}

		DisplayKeyBuffer(1, 2, &key_buffer);
	}

	clrscr();
	printf("Bye!\n");

	return 0;
}



#include <stdio.h>
#include <string.h>

#define MAX_CMD 2048
#define MAX_ARG 256




void ParseCommand(char *command, int *argc, char *argv[]);
int main(){
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1] = 0 ; 

	int argc = 0 ;
	char *argv[MAX_ARG] = {NULL};

	while(1){
		printf("$ ");
		fgets(command, MAX_CMD-1,stdin);
		command[strlen(command) -1] = 0 ;

		if( strcmp(command, "quit") == 0 || strcmp (command, "exit") == 0)
			break;

		ParseCommand(command, &argc, argv);

		printf("argc = %d\n", argc);
		// for(int i = 0 ; i < argc ; i ++)
		// 	printf("argv[%d] = %s\n", i, argv[i]);
		// printf("argv[%d] = %p\n", argc, argv[argc]);
	}

	printf("Bye!\n");

	return 0;
}




void ParseCommand(char *command, int *argc, char *argv[]){

	for(int i = 0 ; i < MAX_ARG ; i++)
		argv[i] = 0 ;

	char *p = strtok(command, " ");
	int count=0;

	while(p != NULL){
		argv[count] = p;

		p = strtok(NULL, " ");
		count++;
	}
	*argc = count;

	if (!strcmp(argv[0],"ls")){
		printf("hi, you entered 'ls'!\n");
	}
  else if (!strcmp(argv[0], "mkdir")){
    printf("hi, you entered 'mkdir'!\n");
  }
  else if (!strcmp(argv[0], "rmdir")){
    printf("hi, you entered 'rmdir'!\n");
  }
  else if (!strcmp(argv[0], "cd")){
    printf("hi, you entered 'cd'!\n");
  }
  else if (!strcmp(argv[0], "curdir")){
    printf("hi, you entered 'curdir'!\n");
  }

}




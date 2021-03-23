
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

#define MAX_CMD 2048
#define MAX_ARG 256




void ParseCommand(char *command, int *argc, char *argv[]);
int main(){
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1] = 0 ; 
  DIR *dp;
  struct dirent *dent;
  char *cwd;
  char wd[BUFSIZ];

	int argc = 0 ;
	char *argv[MAX_ARG] = {NULL};

	while(1){
		printf("$ ");
		fgets(command, MAX_CMD-1,stdin);
		command[strlen(command) -1] = 0 ;

		if( strcmp(command, "quit") == 0 || strcmp (command, "exit") == 0)
			break;

    if(!strcmp(command,"")) continue; // 아무것도 입력하지 않았을 때

		ParseCommand(command, &argc, argv);
    int result = 0;
		  if (!strcmp(argv[0],"ls")){
    system("ls");
	}
  else if (!strcmp(argv[0], "cd")){
    
    if (argv[1]==NULL){
      chdir("~");
    }
    else{
      chdir(argv[1]);
    }
  }
  else if (!strcmp(argv[0], "mkdir")){
    if(argv[1]==NULL){
      printf("usage: mkdir [directory name]\n"); // 명령어만 입력하고 만들 디렉토리를 안 줬을때
    }
    else if(mkdir(argv[1], 0755)== -1){
      perror(argv[1]);
    }
  }
  else if (!strcmp(argv[0], "rmdir")){
    if(argv[1]==NULL){
      printf("usage: rmdir [directory name]\n"); // 명령어만 입력하고 만들 디렉토리를 안 줬을때
    }
    else if(rmdir(argv[1])==-1){
      perror(argv[1]);
    }
    
  }
  
  else if (!strcmp(argv[0], "curdir")){

    cwd = getcwd(NULL, BUFSIZ);
    printf("current directory = %s\n", cwd);
  }
  else{
    printf("%s : command not found\n",argv[0]);
  }
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
}


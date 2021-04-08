#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 512
#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command, int *argc, char *argv[]);
int ReadTextLine(int fd, char str[], int max_len);
void exe_command(char *argv[]);

//global
char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;


int main(int argc, char *argv[])
{
  
    // arg 안줌
    if (argc < 2){
      printf("Usage: %s <command text file>\n", argv[0]);
      return 0;
    }

    // 해당파일 찾을 수가 없음
    if (access(argv[1], F_OK) == -1){
    perror(argv[0]);
    return 0 ;
    }
    
    // 해당 파일 읽을 수가 없음 
    if (access(argv[1], R_OK) == -1){
    perror(argv[1]);
    printf("Err! can not read the file '%s'\n",argv[1]);
    return 0;
    }

    int fd;
    int n=0;
    char buff[BUFFER_SIZE];

    fd = open(argv[1], O_RDONLY);
    while( n != -1){
      n = ReadTextLine(fd, buff, BUFFER_SIZE);

      int command_count =0;
      char *command_slot[BUFFER_SIZE]={NULL};

      
      if(buff[0]=='#')continue; // 커맨드가 아니고 주석인 경우에 생략 
      if(!strcmp(buff,""))continue;
      printf("command = [%s]\n", buff);
      ParseCommand(buff, &command_count, command_slot);
      exe_command(command_slot);
    }   
}
void exe_command(char *argv[]){
    if (!strcmp(argv[0], "cd"))
        {
            if (argv[1] == NULL) // cd 만 입력했을때 홈 디렉토리로 가주는 것
            {
                chdir(getenv("HOME"));
            }
            else if (!strcmp(argv[1],"~")){
                chdir(getenv("HOME"));
            }
            else if (!strcmp(argv[1],"~/")){
                chdir(getenv("HOME"));
            }
            else
            {
                chdir(argv[1]);
            }
        }
    else {
      
      pid_t pid = fork();

      if (pid<0){
        printf("fork failed\n");
        exit(-1);
      } else if (pid == 0 ){
        execvp(argv[0], argv);
      }
        wait(NULL);
    }
}

int ReadTextLine(int fd, char str[], int max_len)
{
    int i = 0;
    int j = 0;
    int ret = 0;

    // if current position is 0,
    // // reset buffer size and pos
    if (lseek(fd, 0, SEEK_CUR) == 0)
        buffer_pos = buffer_size = 0;

    while (j < max_len - 1)
    {
        if (buffer_pos == buffer_size)
        {
            buffer[0] = 0;
            buffer_size = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
        }

        if (buffer_size == 0)
        {
            if (j == 0)
                ret = EOF;
            break;
        }

        while (j < max_len - 2 && buffer_pos < buffer_size)
        {
            str[j++] = buffer[buffer_pos++];
            if (str[j - 1] == '\0' || str[j - 1] == 10)
            {
                j--;
                max_len = j;
                break;
            }
        }
    }
    str[j] = 0;
    return ret;
}

void ParseCommand(char *command, int *argc, char *argv[])
{

    for (int i = 0; i < MAX_ARG; i++)
        argv[i] = 0;

    char *p = strtok(command, " ");
    int count = 0;

    while (p != NULL)
    {
        argv[count] = p;

        p = strtok(NULL, " ");
        count++;
    }
    *argc = count;
}

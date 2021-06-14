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

    // char *strtok(char *_String, char const *"Delimiter);
    // 포인터 리턴 : strtok(자를 src String, 기준이 되는 문자열);
    char *p = strtok(command, " "); // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    int count = 0;

    while (p != NULL)
    {
        argv[count] = p;

        /* 
            NULL을 넣었을 때는 직전 strtok 함수에서 처리했던 문자열에서
            잘린 문자열만큼 다음 문자로 이동한 뒤 다음 문자열을 자릅니다.
            만약 ptr = strtok(ptr, " ");처럼 잘린 문자열의 포인터를
            다시 넣었을 때는 다음 문자로 이동하지 못하고 처음에 나오는 문자열만 계속 자르게 됩니다.

            ! strtok 함수는 문자열을 새로 생성해서 반환하는 것이 아니라 자르는 부분을 널 문자(NULL)로 채운 뒤 잘린 문자열의 포인터를 반환합니다.
            따라서 원본 문자열의 내용을 바꾸므로 사용에 주의해야 합니다.
         */
        p = strtok(NULL, " "); 
        count++;
    }
    *argc = count;
}

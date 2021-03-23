#include <stdio.h>

int main(int argc, char *argv[])      // 옵션의 개수와 옵션 문자열을 배열로 받음
{
    for (int i = 0; i < argc; i++)    // 옵션의 개수만큼 반복
    {
        printf("i = %d : %s\n", i,argv[i]);      // 옵션 문자열 출력
    }

    char superDir[BUFSIZ];
    char targetFile[BUFSIZ];

    if (argv[1] == NULL){
      printf("optional err");
      printf("usage : ./program [super directory] [target file name]\n");
      exit(1);
    }
    if (argv[2] == NULL){
      printf("optional err2");
      printf("usage : ./program [super directory] [target file name]\n");
      exit(1);
    }


    


    return 0;
}
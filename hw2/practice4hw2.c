#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
//  디렉토리 생성 명령어 : path에 지정한 디렉토리를 mode 권한에 따라 생성한다.
// int mkdir(const char *path, mode_t mode);
// 디렉토리 삭제 명령어
// int rmdir(const char *path);
// 현재 디렉토리 위치 (pwd)
// char *getcwd(char *buf, size_t size);
// 디렉토리 이동 chdir (cd)
// int chdir(const char *path);
// 디렉토리 열기
// DIR *opendir(const char *dirname);
// 디렉토리 정보 읽기 (ls)
// readdir ..
// 디렉토리 닫기
// int closedir(DIR *dirp);
// 리눅스 명령어 해쥼
// int system(const char * str

int main()
{
    DIR *dp;
    struct dirent *dent;
    char *cwd;
    char wd[BUFSIZ];

    system("ls");

    if ((dp = opendir(".")) == NULL)
    {
        perror("opendir : hanbit");
        exit(1);
    }
    printf("ls\n");
    while ((dent = readdir(dp)))
    {
        printf("name :%s ", dent->d_name);
        printf("type : %c\n", dent->d_type);
    }
    printf("\n");

    closedir(dp);

    if (mkdir("ahnssuTest", 0755) == -1)
    {
    }

    printf("pwd\n");
    cwd = getcwd(NULL, BUFSIZ);
    printf("1. Current Directory : %s\n", cwd);

    printf("cd ahnssuTest\n");
    chdir("ahnssuTest");
    system("ls");

    if ((dp = opendir(".")) == NULL)
    {
        perror("opendir : hanbit");
        exit(1);
    }
    printf("ls\n");
    while ((dent = readdir(dp)))
    {
        printf("name :%s ", dent->d_name);
        printf("type : %d\n", dent->d_type);
    }
    printf("\n");

    closedir(dp);

    cwd = getcwd(NULL, BUFSIZ);
    printf("2. Current Directory : %s\n", cwd);

    printf("cd ..\n");
    chdir("..");

    if ((dp = opendir(".")) == NULL)
    {
        perror("opendir : hanbit");
        exit(1);
    }
    printf("ls\n");
    while ((dent = readdir(dp)))
    {
        printf("name :%s ", dent->d_name);
        printf("type : %d\n", dent->d_type);
    }
    printf("\n");

    closedir(dp);

    cwd = getcwd(NULL, BUFSIZ);
    printf("3. Current Directory : %s\n", cwd);

    printf("rmdir ahnssuTest");
    rmdir("ahnssuTest");

    if ((dp = opendir(".")) == NULL)
    {
        perror("opendir : hanbit");
        exit(1);
    }
    printf("ls\n");
    while ((dent = readdir(dp)))
    {
        printf("name :%s ", dent->d_name);
        printf("type : %d\n", dent->d_type);
    }
    printf("\n");

    closedir(dp);
}
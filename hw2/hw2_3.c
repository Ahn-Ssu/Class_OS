
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

#define MAX_CMD 2048
#define MAX_ARG 256
#define MAX_PATH 256

void ParseCommand(char *command, int *argc, char *argv[]);
int FindFile(char *start_dir, char *target, char *path);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <start_dir> <target_file>\n", argv[0]);
        return 0;
    }

    char *start_dir = argv[1];
    char *target = argv[2];
    char path[MAX_PATH] = "";

    int ret = FindFile(start_dir, target, path);

    if (ret)
        printf("path = %s\n", path);
    else
        printf("Cannot find %s\n", target);

    return 0;
}

int FindFile(char *start_dir, char *target, char *path)
{

    DIR *dp;
    struct dirent *dent;

    if ((dp = opendir(start_dir)) == NULL)
    {
        return 0;
    }

    while ((dent = readdir(dp)))
    {

        if ((!strcmp(dent->d_name, target)) &&
            (dent->d_type != 4))
        {

            char location[MAX_PATH] = "";

            strcat(location, start_dir);
            strcat(location, "/");
            strcat(location, target);
            strcat(path, location);

            closedir(dp);
            return 1;
        }
    }
    closedir(dp);

    if ((dp = opendir(start_dir)) == NULL)
    {
        printf("oper false in 2");
        return 0;
    }

    int result = 0;
    while ((dent = readdir(dp)))
    {

        if (dent->d_type == 4)
        {

            if (
                strcmp(dent->d_name, ".") &&
                strcmp(dent->d_name, ".."))
            {

                char sub[MAX_PATH] = "";

                strcat(sub, start_dir);
                strcat(sub, "/");
                strcat(sub, dent->d_name);

                result = FindFile(sub, target, path);

                if (result)
                {

                    closedir(dp);
                    return 1;
                }
            }

            int result = 0;
        }
    }
    closedir(dp);

    // int result = 0 ;
    // if ((dp = opendir(start_dir)) == NULL){
    //   printf("oper false in 2");
    //     return 0;
    // }

    // while (( dent = readdir(dp))){
    //     if (dent-> d_type == 4 && strcmp(dent->d_name,".") && strcmp(dent->d_name,"..")){
    //       printf("searching dir : %s\n",dent->d_name);
    //       printf("\n");
    //         result = FindFile(strcat(strcat(start_dir,"/"),dent->d_name), target, path);
    //         if (result){
    //             closedir(dp);
    //             return 1;
    //         }
    //     }
    // }
    // closedir(dp);

    return 0;
}
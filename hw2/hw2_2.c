
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>


int main()
{
    DIR *dp;
    struct dirent *dent;
    char wd[BUFSIZ];

    if (( dp = opendir(".")) == NULL){
        perror("opendir : './'");
        exit(1);
    }
    
    while (( dent = readdir(dp))){
        printf("%s ", dent->d_name);
        if (dent->d_type == 4){
            printf("[directory]\n");
        }
        else printf("\n");
    }

    closedir(dp);
    

    return 0;
}

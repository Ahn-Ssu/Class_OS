#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int mkdirs(const char *path, mode_t mode)
{
    char temp_path[2048];
    const char *temp = path;
    int len = 0;
    int ret;

    if (path == NULL || strlen(path) >= 2048)
    {
        return -1;
    }

    while ((temp = strchr(temp, '/')) != NULL)
    {
        len = temp - path;
        temp++;

        if (len == 0)
            continue;

        strncpy(temp_path, path, len);
        temp_path[len] = 0x00;

        if ((ret = mkdir(temp_path, mode)) == -1)
        {
            if (errno != EEXIST)
                return -1;
        }
    }

    return mkdir(path, mode);
}

int main()
{
    return mkdirs("./src/temp", 0776);
}
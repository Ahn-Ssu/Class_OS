#include <sys/stat.h>   // for open
#include <fcntl.h>      // for open
#include <unistd.h>     // for read, write, close 


int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int close(int fd);

ssize_t read(int fd, void *buf, size_t count);

ssize_t write(int fd, const void *buf, size_t count);
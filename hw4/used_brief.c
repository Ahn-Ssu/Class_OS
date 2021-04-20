/* list 
1)
    -- POSIX Shared Memory 
    shm_open()
    shm_unlink()
    mmap()
    munmmap()
*/


// shm_open()
#include <sys/mman.h>       // for shm_open(), shm_unlink(), mmap(), munmap()
#include <sys/stat.h>       // for shm_open(), shm_unlink()
#include <fcntl.h>          // for shm_open(), shm_unlink()

int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);
void *mmap(void  *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
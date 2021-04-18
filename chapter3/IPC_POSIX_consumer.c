#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(){
    // the size (in bytes) of shared memory object 
    const int SIZE = 4096;
    // name of the shared memory bject 
    const char *name = "OS";
    // shared memory file desciptor
    int shm_fd;
    //  pointer to shared memory object
    void *ptr;


    // create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);


    // memory map the shared memory object
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // read from the shared memory object
    printf("%s", (char *) ptr);

    // remove the shared memory object
    shm_unlink(name);

    return 0;
}
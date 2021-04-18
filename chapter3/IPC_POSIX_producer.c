#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(){
    // the size (in bytes) of shared memory object 
    const int SIZE = 4096;
    // name of the shared memory bject 
    const char *name = "OS";
    //  strings written to shared memory 
    const char *message0 = "Hello";
    const char *message1 = "World!";

    // shared memory file desciptor
    int shm_fd;
    //  pointer to shared memory object
    void *ptr;


    // create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // configure the size of the sharred memory object
    ftruncate(shm_fd, SIZE);

    // memory map the shared memory object
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // write to the shared memory object
    sprintf(ptr, "%s", message0);
    ptr += strlen(message0);
    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);

    return 0;
}
#include <stdio.h>
#include <unistd.h>


int main(int args, char *argv[]){

  printf("User and Process info:\n");
  printf("    getuid() = %d\n", getuid());
  printf("    getpid() = %d\n", getpid());
  printf("    getppid() = %d\n", getppid());
}


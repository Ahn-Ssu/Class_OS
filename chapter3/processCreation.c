#include <stdio.h>

#include <stdlib.h>

#include <unistd.h> // fork() 와 exec() family가 담겨있는 헤더
#include <sys/wait.h>  // wait()
#include <sys/types.h> // wait()

int main()
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        fprintf(stderr, "fork ffailed\n");
        exit(-1);
    }
    else if (child_pid == 0)
    {
        printf("hi I'm child, my pid is [%d]\n",child_pid);
        execlp("/bin/ls", "ls", NULL);
        // execlp 밑으로는 실행이 안됨 
        printf("hi I'm child, my pid is [%d]\n",child_pid);
        printf("done \n\n");
    }
    else
    {
        printf("hi I'm parent, my pid is [%d]\n",child_pid);
        wait(NULL);
        printf("Child Completed\n");
        exit(0);
    }

    return 0;
}
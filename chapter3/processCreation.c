#include <stdio.h>

#include <stdlib.h>

#include <unistd.h> // fork() 와 exec() family가 담겨있는 헤더
#include <sys/wait.h>  // wait()
#include <sys/types.h> // wait()

int main()
{
    printf("%d\n",(int)getpid());
    pid_t child_pid = fork();


    
    if (child_pid < 0)
    {
        fprintf(stderr, "fork ffailed\n");
        exit(-1);
    }
    else if (child_pid == 0) // child
    {
        printf("hi I'm child, my var:child_pid is [%d]\n",child_pid); 
        printf("hi I'm child, my _pid is [%d]\n", (int)getpid());
        execlp("/bin/ls", "ls", NULL);
    }
    else // parent
    {
        printf("hi I'm parent, my var:child_pid  is [%d]\n",child_pid);
        printf("hi I'm parent, my _pid is [%d]\n", (int)getpid());
        wait(NULL);
        printf("Child Completed\n");
        exit(0);
    }

    return 0;
}

//getpid는 실행중인 프로세스 id를 받아오고 fork로 받아오는 pid는 부모 프로세스의 pid를 받거나 차일드인경우 0을 받음

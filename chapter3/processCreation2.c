#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("pid : %d\n", (int) getpid()); // pid : 29146
    
    int rc = fork();			// 주목
    
    if (rc < 0) {			// (1) fork 실패
        exit(1);
    }							
    else if (rc == 0) {			// (2) child 인 경우 (fork 값이 0)
        printf("child (pid : %d)\n", (int) getpid());
    }
    else {				// (3) parent case
        int wc = wait(NULL);		// 추가된 부분
        printf("parent of %d (wc : %d / pid : %d)\n", wc, rc, (int)getpid());
    }
}
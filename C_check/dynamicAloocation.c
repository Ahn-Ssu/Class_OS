#include <stdio.h>
#include <stdlib.h>

int main(){

    int a[5]={0};
    int *p = NULL;

    p = (int*)malloc(5*sizeof(int));

    printf("\narray %p | dynamic array %p | same? %s\n", a, p, a==p?"Yes":"No");

    free(p);
    printf("Clear free dA\n");

    free(a);
    printf("Clear free sA\n");
}
// https://stackoverflow.com/questions/10716013/can-i-free-static-and-automatic-variables-in-c 
// static과 automatic variables 에게 free를 수행하면 정해지지 않은 동작을 수행함 
// 컴파일러는 이걸 처리할 필요도 없고, 중단(abort)로 프로그램의 실행을 끊어버림 SIGABRT 6 : Abort trap: 6
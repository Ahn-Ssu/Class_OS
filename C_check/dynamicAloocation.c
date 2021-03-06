#include <stdio.h>
#include <stdlib.h>
#define type(x) _Generic((x),                                                     \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "char *",                 \
       void *: "void *",                         int *: "int *",                  \
      default: "unknown")

int main(){

    int a[5]={0};
    int *p = NULL;

    p = (int*)malloc(5*sizeof(int));

    printf("\narray %p | dynamic array %p | same? %s\n", a, p, a==p?"Yes":"No");

    printf("type\narray %s | dynamic array %s | same? %s\n", type(a), type(p), a==p?"Yes":"No");

    free(p);
    printf("Clear free dA\n");
    printf("p -> ? %p\n", p);
    printf("p is null? %s \n" , p==NULL?"Yes":"No");
//     free를 수행해도, NULL 포인터가 되지 않는다는 것을 알아야함 


    free(a);
    printf("Clear free sA\n");
}
// https://stackoverflow.com/questions/10716013/can-i-free-static-and-automatic-variables-in-c 
// static과 automatic variables 에게 free를 수행하면 정해지지 않은 동작을 수행함 
// 컴파일러는 이걸 처리할 필요도 없고, 중단(abort)로 프로그램의 실행을 끊어버림 SIGABRT 6 : Abort trap: 6
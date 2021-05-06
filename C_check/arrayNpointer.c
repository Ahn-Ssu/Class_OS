#include <stdio.h>

int main()
{
    int a[5] = {2, 4, 6, 8 , 22};
    int *p; 

    p = &a[1];

    printf(" %d | %d | same? %s\n", a[0], p[0], a[0]==p[0]?"Yes":"No");
    printf(" %p | %p | same? %s\n", a, p, a==p?"Yes":"No");

    p = p -1 ; 
    // a = a + 1; a+1은 포인터 변수에 상수 연산을 적용하는 것처럼 연산이 진행되지만 
    // a ++; 그 이후에 증가된 주소값을 다시 a에 assign하는 것은 불가능하다. a는 상수이기 때문.
    // 어셈블리 코드에 보면, 배열은 선언이 되어버린 후에 동작을 하기 때문에 constant 동작이 됨
    // 10 = 10+1의 동작을 하는 것과 동일함.

    printf(" %d | %d | same? %s\n", a[0], p[0], a[0]==p[0]?"Yes":"No");
    printf(" %p | %p | same? %s\n", a, p, a==p?"Yes":"No");

    // 배열에 연산 자체는 가능함 
    printf(" %p | %p | same? %s\n", a, a+1, a==(a+1)?"Yes":"No");

}
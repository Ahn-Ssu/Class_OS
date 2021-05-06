#include <stdio.h>

int main()
{
    int a[5] = {2, 4, 6, 8 , 22};
    int *p; 

    p = &a[1];

    printf(" %d | %d | same? %s\n", a[0], p[0], a[0]==p[0]?"Yes":"No");
    printf(" %p | %p | same? %s\n", a, p, a==p?"Yes":"No");

    p = p -1 ; 
    // a = a + 1;
    // a ++;

    printf(" %d | %d | same? %s\n", a[0], p[0], a[0]==p[0]?"Yes":"No");
    printf(" %p | %p | same? %s\n", a, p, a==p?"Yes":"No");

}
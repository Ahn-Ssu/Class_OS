#include <stdio.h>

void show(int a){
    printf("%d \n",a); 
}

int main(void){
    int aa = 10;
    void(*show_ptr)(int) = show;
    
    printf("%p %p %p \n",show,&show,show_ptr);

    show(aa);
    show_ptr(aa);


    printf("main = %p\n", main);
    printf("&main = %p\n", &main);

    return 0;
}
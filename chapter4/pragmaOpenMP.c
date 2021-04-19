#include <stdio.h>

int main(){

    int i = 0 ;

    #pragma omp parallel
        printf("[%d], Hello Wolrd\n", ++i);

    #pragma omp parallel for
        for(i=0; i < 20 ; i ++){
            printf("[%d], Hi omp\n", i);
        }
}
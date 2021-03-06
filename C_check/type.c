#include <stdio.h>

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

int main() {
    char  ch;
    int   a;
    long  b;
    char* str;
    char  str2[5];

    printf( "%s\n", type(ch)   ); // char
    printf( "%s\n", type(a)    ); // int
    printf( "%s\n", type(b)    ); // long int
    printf( "%s\n", type(str)  ); // char *
    printf( "%s\n", type(str2) ); // char *
}
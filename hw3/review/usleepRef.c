#include <stdio.h>
#include <unistd.h>

int main( void)
{
   while( 1)
   {
      printf( "1초 마다 문자열 출력\n");
      usleep( 1000 * 1000 );
   }
}
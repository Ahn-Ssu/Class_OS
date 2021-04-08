#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/param.h>
 
int main(int argc, char **argv)
{
    struct utsname un;
 
    uname(&un);
 
    printf("o/s name: %s\n", un.sysname);
    printf("node name:%s\n", un.nodename);
    printf("release:%s\n",un.release);
    printf("version:%s\n",un.version);
    printf("machine:%s\n",un.machine);
 
    char hn[MAXHOSTNAMELEN]="";
    gethostname(hn,MAXHOSTNAMELEN);
    printf("host name:%s\n",hn);
 
    return 0;
}